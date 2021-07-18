#ifndef __usbd_driver__h
#define __usbd_driver__h
#include "stm32f4xx.h"                  // Device header
#include "stm32f429xx.h"
#include "usb_standards.h"
#include "usb_standards.h"
#include "helperv2.h"
#define USB_OTG_HS_GLOBAL ((USB_OTG_GlobalTypeDef *)(USB_OTG_HS_PERIPH_BASE + USB_OTG_GLOBAL_BASE))
#define USB_OTG_HS_DEVICE ((USB_OTG_DeviceTypeDef *)(USB_OTG_HS_PERIPH_BASE + USB_OTG_DEVICE_BASE))
#define USB_OTG_HS_PCGCCTL ((__IO uint32_t *)(USB_OTG_HS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE)) // Power and clock gating control register

/** \brief Returns the structure contains the registers of a specific IN endpoint.
 * \param endpoint_number The number of the IN endpoint we want to access its registers.
 */
inline static USB_OTG_INEndpointTypeDef * IN_ENDPOINT(uint8_t endpoint_number)
{
    return (USB_OTG_INEndpointTypeDef *)(USB_OTG_HS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (endpoint_number * 0x20));
}

/** \brief Returns the structure contains the registers of a specific OUT endpoint.
 * \param endpoint_number The number of the OUT endpoint we want to access its registers.
 */
inline static USB_OTG_OUTEndpointTypeDef * OUT_ENDPOINT(uint8_t endpoint_number)
{
    return (USB_OTG_OUTEndpointTypeDef *)(USB_OTG_HS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (endpoint_number * 0x20));
}

inline static __IO uint32_t *FIFO(uint8_t endpoint_number)
{
    return (__IO uint32_t *)(USB_OTG_HS_PERIPH_BASE + USB_OTG_FIFO_BASE + (endpoint_number * 0x1000));
}

/// \brief Total count of IN or OUT endpoints.
#define ENDPOINT_COUNT 6

/// \brief USB driver functions exposed to USB framework.
typedef struct
{
	void (*initialize_core)();
	void (*initialize_gpio_pins)();
	void (*set_device_address)(uint8_t address);
	void (*connect)();
	void (*disconnect)();
	void (*flush_rxfifo)();
	void (*flush_txfifo)(uint8_t endpoint_number);
	void (*configure_in_endpoint)(uint8_t endpoint_number, enum UsbEndpointType endpoint_type, uint16_t endpoint_size);
	void (*read_packet)(void const *buffer, uint16_t size);
	void (*write_packet)(uint8_t endpoint_number, void const *buffer, uint16_t size);
	void (*poll)();
	// ToDO Add pointers to the other driver functions.
} UsbDriver;

extern const UsbDriver usb_driver;
extern UsbEvents usb_events;

#endif

