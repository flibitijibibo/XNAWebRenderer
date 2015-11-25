#include "include/cef_app.h"
int main(int argc, char **argv)
{
#ifdef _WIN32
	CefMainArgs args(GetModuleHandle(NULL));
#else
	CefMainArgs args(argc, argv);
#endif
	return CefExecuteProcess(args, NULL, NULL);
}
