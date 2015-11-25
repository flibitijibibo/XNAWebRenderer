/* XNAWebRenderer - Portable Webpage Renderer for XNA Games
 *
 * Copyright (c) 2015 Ethan Lee.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software in a
 * product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Ethan "flibitijibibo" Lee <flibitijibibo@flibitijibibo.com>
 *
 */

#include "XNAWebRenderer.h"

#include <assert.h>

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

/* Remove printf if you don't want to spam stdout -flibit */
#define DEBUGLOG printf

/* Extra process so we don't have to worry about argv */
#ifdef _WIN32
#define PROCPATH "cefprocess.exe"
#elif __APPLE__
#define PROCPATH "./cefprocess.bin.osx"
#elif __linux__
#ifdef __x86_64__
#define PROCPATH "./cefprocess.bin.x86_64"
#else
#define PROCPATH "./cefprocess.bin.x86"
#endif
#else
#error Unhandled platform!
#endif

class GLRenderHandler : public CefRenderHandler
{
public:
	/* Our stuff */
	TextureUpdatedDelegate textureUpdated;
	int w, h;
	GLRenderHandler(TextureUpdatedDelegate callback, int width, int height)
	{
		textureUpdated = callback;
		w = width;
		h = height;
	}
	~GLRenderHandler()
	{
		DEBUGLOG("GLRenderHandler close\n");
	}

	/* Chromium's stuff */
	bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
	{
		DEBUGLOG("GetViewRect\n");
		rect = CefRect(0, 0, w, h);
		return true;
	}
	void OnPaint(
		CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList &dirtyRects,
		const void *buffer,
		int width,
		int height
	) {
		DEBUGLOG("OnPaint\n");
		/* FIXME: You assholes seriously couldn't make a flag that lets
		 * you pick the surface format?
		 * -flibit
		 */
		char *buf = (char*) buffer;
		for (int i = 0; i < width * height * 4; i += 4)
		{
			char temp = buf[i];
			buf[i] = buf[i + 2];
			buf[i + 2] = temp;
		}
		textureUpdated(buffer);
	}
	IMPLEMENT_REFCOUNTING(GLRenderHandler);
};

class GLClient : public CefClient
{
public:
	CefRefPtr<CefRenderHandler> handler;
	GLClient(TextureUpdatedDelegate callback, int width, int height)
	{
		handler = new GLRenderHandler(callback, width, height);
	}
	~GLClient()
	{
		handler = NULL;
		DEBUGLOG("GLClient close\n");
	}
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler()
	{
		DEBUGLOG("GetRenderHandler\n");
		return handler;
	}
	IMPLEMENT_REFCOUNTING(GLClient);
};

static unsigned int refcount = 0;
static CefRefPtr<GLClient> client;
static CefRefPtr<CefBrowser> browser;

void XNAWR_Initialize(
	const char *initialURL,
	TextureUpdatedDelegate callback,
	int width,
	int height
) {
	if (refcount == 0)
	{
		CefMainArgs args;
		CefSettings settings;
		settings.windowless_rendering_enabled = true;
		CefString(&settings.browser_subprocess_path).FromASCII(PROCPATH);
		if (!CefInitialize(args, settings, NULL, NULL))
		{
			assert(0 && "CefInitialize failed!");
		}
		client = new GLClient(
			callback,
			width,
			height
		);
		CefWindowInfo windowInfo;
		windowInfo.windowless_rendering_enabled = true;
		CefBrowserSettings browserSettings;
		browser = CefBrowserHost::CreateBrowserSync(
			windowInfo,
			client.get(),
			initialURL,
			browserSettings,
			NULL
		);
	}
	refcount += 1;
}

void XNAWR_Shutdown()
{
	assert(refcount > 0);
	refcount -= 1;
	if (refcount == 0)
	{
		client = NULL;
		browser = NULL;
		CefShutdown();
	}
}

void XNAWR_Update()
{
	CefDoMessageLoopWork();
}

void XNAWR_LoadURL(const char *URL)
{
	browser->GetMainFrame()->LoadURL(URL);
}

void XNAWR_SetViewport(int width, int height)
{
	GLRenderHandler* handler = (GLRenderHandler*) client->handler.get();
	handler->w = width;
	handler->h = height;
	browser->GetHost()->WasResized();
}
