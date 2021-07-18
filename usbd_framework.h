#ifndef __usbd_framework__h
#define __usbd_framework__h
#include "usbd_driver.h"
#include "helperv2.h"
#include "usb_device.h"
void usbd_initialize(UsbDevice *usb_device);
void usbd_poll(void);

#endif

