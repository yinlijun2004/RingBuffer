/*
 *  app_sys_log.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <android/log.h>
#include "app_sys_log.h"

#define __LOG_TAG__		"TRENDIT"

void app_sys_info(const char* pMessage, ...)
{
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_INFO, __LOG_TAG__, pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_INFO, __LOG_TAG__, "\n");
	va_end(lVarArgs);
}

void app_sys_error(const char* pMessage, ...)
{
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_ERROR, __LOG_TAG__, pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_ERROR, __LOG_TAG__, "\n");
	va_end(lVarArgs);

}
void app_sys_warn(const char* pMessage, ...)
{
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_WARN, __LOG_TAG__, pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_WARN, __LOG_TAG__, "\n");
	va_end(lVarArgs);

}
void app_sys_debug(const char* pMessage, ...)
{
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_DEBUG, __LOG_TAG__, pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_DEBUG, __LOG_TAG__, "\n");
	va_end(lVarArgs);

}

void app_sys_dump(const char * str, unsigned char * pBuf, unsigned int len)
{
	unsigned int i, j, nRemain;
	char tmp[17];
	char *p;
	char *add = pBuf;
	unsigned int nLine = 0;

	char strLine[48];
	int byte_per_len = 12;

	if(str)
		app_sys_info("%s: length = %d [0x%X]\r\n", str, len, len);



	if(len == 0)
		return;

	nLine = len / byte_per_len;

	for(i = 0; i < nLine; i++)
	{
		memset(strLine, 0, sizeof(strLine));
		for(j = 0; j < byte_per_len; j++)
			sprintf(strLine + 3 * j, "%02X ", *add++);
		__android_log_print(ANDROID_LOG_DEBUG, __LOG_TAG__, "%s\n", strLine);
	}

	nRemain = len % byte_per_len;
	if(nRemain)
	{
		memset(strLine, 0, sizeof(strLine));
		for(j = 0; j < nRemain; j++)
			sprintf(strLine + 3 * j, "%02X ", *add++);
		__android_log_print(ANDROID_LOG_DEBUG, __LOG_TAG__, "%s\n", strLine);

	}

	return;
}







