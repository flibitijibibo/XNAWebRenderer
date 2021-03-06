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

#ifndef XNAWEBRENDERER_H
#define XNAWEBRENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
	#define EXPORTFN __declspec(dllexport)
	#define DELEGATECALL __stdcall
#else
	#define EXPORTFN
	#define DELEGATECALL
#endif

typedef void (DELEGATECALL *TextureUpdatedDelegate)(const void*);

EXPORTFN void XNAWR_Initialize(
	const char *initialURL,
	TextureUpdatedDelegate callback,
	int width,
	int height
);

EXPORTFN void XNAWR_Shutdown();

EXPORTFN void XNAWR_Update();

EXPORTFN void XNAWR_LoadURL(const char *URL);

EXPORTFN void XNAWR_SetViewport(int width, int height);

#undef EXPORTFN
#undef DELEGATECALL

#ifdef __cplusplus
}
#endif

#endif /* XNAWEBRENDERER_H */
