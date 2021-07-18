#include "helperv2.h"

struct FILE {int handle;/* Add whatever you need here */};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
  ITM_SendChar(ch);
  return(ch);
}


void log_error(char *p)
{

	printf("log Error: ");

		printf((char*)p);
printf("\r\n");


}

void log_info(char *p)
{

	printf("log info: ");

		printf((char*)p);
printf("\r\n");


}

void log_debug(char *p)
{

	printf("log debug: ");

		printf((char*)p);
printf("\r\n");


}

void log_debug_array(char const * const label, void const *array, uint16_t const len)
{
  	printf("log debug array: ");
       
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