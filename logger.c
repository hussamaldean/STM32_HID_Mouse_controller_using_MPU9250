

#include "logger.h"
#include "stm32f4xx.h"
LogLevel system_log_level= LOG_LEVEL_DEBUG;
/** \brief Redirects `printf()` output to the serial wire out (SWO).
 * This function overrides a weak function symbol and is not to be used directly.
 */

 struct __FILE {int handle;/* Add whatever you need here */};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
  ITM_SendChar(ch);
  return(ch);
}

 
int _write(int file, char *ptr, int len)
{

  int i=0;
  for(i=0 ; i<len ; i++)
	{
    //ITM_SendChar((*ptr++));
		printf((char )(ptr++));
	}
//fputc((*ptr++));
  return len;
}

char const * const _get_log_level_string(LogLevel const log_level)
{
    switch(log_level)
    {
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_INFORMATION:
            return "INFO";
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
    }
}

static void _log(LogLevel const log_level, char const * const format, va_list args)
{
    if (log_level > system_log_level)
        return;

	printf("[%s] ", _get_log_level_string(log_level));
	vfprintf(stdout, format, args);
	printf("\n");
}

void log_error(char const * const format, ...)
{
    va_list args;
	va_start(args, format);
    _log(LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

void log_info(char const * const format, ...)
{
    va_list args;
	va_start(args, format);
    _log(LOG_LEVEL_INFORMATION, format, args);
    va_end(args);
}

void log_debug(char const * const format, ...)
{
    va_list args;
	va_start(args, format);
    _log(LOG_LEVEL_DEBUG, format, args);
    va_end(args);
}

/** \brief Log the content of an array.
 * \param label The label of the array.
 * \param array Pointer to the array.
 * \param len The length of data in bytes.
 */
void log_debug_array(char const * const label, void const *array, uint16_t const len)
{
    if (LOG_LEVEL_DEBUG > system_log_level)
        return;
        
	printf("[%s] %s[%d]: {", _get_log_level_string(LOG_LEVEL_DEBUG), label, len);
    for (uint16_t i = 0; i < len; i++)
    {
    	uint8_t val = *((uint8_t *)(array + i));
    	printf("0x%02X", val);
    	
    	// Add ", " after all elements except the last one.
    	if (i < len - 1)
    	{
    	    printf(", ");
    	}
    }
	printf("}\n");
}
