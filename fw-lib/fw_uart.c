#include "fw_uart.h"
#include "stdarg.h"
#include "stdio.h"


void PCInit(uint32 baud)
{
	sciInit();
	sciSetBaudrate(PC_UART, baud);
}

void fwprintf(const char* _format, ...)
{
	char str[128];
	int8_t length = -1;

	va_list args;
	va_start(args, _format);

	length = vsnprintf(str, sizeof(str), _format, args);

	va_end(args);

	if (length > 0)
	{
		sciSend(PC_UART, (unsigned) length, (unsigned char*) str);
		sciSend(PC_UART, 2, "\r\n");
	}
}
