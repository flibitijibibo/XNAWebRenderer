#region License
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
#endregion

#region Using Statements
using System;
using System.Runtime.InteropServices;
#endregion

public static class XNAWebRenderer
{
	private const string nativeLibName = "XNAWebRenderer.dll";

	#region Public Function Pointer Types

	public delegate void TextureUpdatedDelegate(IntPtr buffer);

	#endregion

	#region Public Static Methods

	/* It is strongly recommended that you get the argv0 path like so:
	 *
	 * string os = SDL2.SDL.SDL_GetPlatform();
	 * string exePath = AppDomain.CurrentDomain.FriendlyName;
	 * if (os.Equals("Linux"))
	 * {
	 *	exePath = exePath.Replace("exe", "bin.x86");
	 *	if (IntPtr.Size == 8)
	 *	{
	 *		exePath += "_64";
	 *	}
	 * }
	 * else if (os.Equals("Mac OS X"))
	 * {
	 *	exePath = exePath.Replace("exe", "bin.osx");
	 * }
	 * else if (!os.Equals("Windows"))
	 * {
	 *	throw new NotSupportedException("Unhandled SDL2 platform!");
	 * }
	 * string result = Path.Combine(
	 *	AppDomain.CurrentDomain.BaseDirectory,
	 *	exePath
	 * );
	 *
	 * -flibit
	 */
	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern void XNAWR_Initialize(
		[MarshalAs(UnmanagedType.LPStr)]
			string argv0,
		[MarshalAs(UnmanagedType.LPStr)]
			string initialURL,
		TextureUpdatedDelegate callback,
		int width,
		int height
	);

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern void XNAWR_Shutdown();

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern void XNAWR_Update();

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern void XNAWR_LoadURL(
		[MarshalAs(UnmanagedType.LPStr)]
			string URL
	);

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern void XNAWR_SetViewport(int width, int height);

	#endregion
}
