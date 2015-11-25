#include "include/cef_app.h"
#ifdef _WIN32
#include <windows.h>
#endif
int main(int argc, char **argv)
{
#ifdef _WIN32
	CefMainArgs args(GetModuleHandle(NULL));
#else
	CefMainArgs args(argc, argv);
#endif
	return CefExecuteProcess(args, NULL, NULL);
}
