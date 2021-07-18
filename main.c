#include "usbd_framework.h"
#include "usb_device.h"
#include "helperv2.h"
#include "MPU9250.h"
UsbDevice usb_device;
uint32_t buffer[8];
extern void blink_init();

 
int main()

{
log_info("entry point of the code");
SystemCoreClockUpdate();
blink_init();
I2C3_Init();
MPU9250_beginAccel(ACC_FULL_SCALE_16_G);
usb_device.ptr_out_buffer=buffer;
usbd_initialize(&usb_device);
	while(1)
	{
		
		usbd_poll();	
	}
}

