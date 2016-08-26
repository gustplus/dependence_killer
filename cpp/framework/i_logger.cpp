#include "i_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

ILogger *ILogger::s_instance = NULL;

void ILogger::Log(const char *format, ...) {
	va_list args;
	va_start(args, format);
	char buf[1024] = {0};
	vsnprintf(buf, 1024, format, args);
	va_end(args);
	printf("%s", buf);
	int len = strlen(buf);
	Log(buf, len);
}
