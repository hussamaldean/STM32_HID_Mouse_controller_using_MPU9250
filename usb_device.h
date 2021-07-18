#ifndef __usb_device__h
#define __usb_device__h

#include "usb_standards.h"

typedef struct
{
	/// \brief The current USB device state.
	UsbDeviceState device_state;
	/// \brief The current control transfer stage (for endpoint0).
	UsbControlTransferStage control_transfer_stage;
	/// \brief The selected USB configuration.
	uint16_t configuration_value;

	/** \defgroup UsbDeviceOutInBufferPointers
	 *@{*/
	void const *ptr_out_buffer;
	uint32_t out_data_size;
	void const *ptr_in_buffer;
	uint32_t in_data_size;
	/**@}*/
} UsbDevice;





#endif 

