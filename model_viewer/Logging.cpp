#include "Logging.h"

#ifdef _DEBUG
void MVDebugLog(const char* format, ...)
{
	char buff[1024];
	va_list arg;
	va_start(arg, format);
	_vsnprintf(buff, sizeof(buff), format, arg);
	va_end(arg);

	OutputDebugString(buff);
}
#endif
