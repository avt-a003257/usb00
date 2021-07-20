#ifndef _USBCORE_H_
#define _USBCORE_H_

#include "common.h"

/* Table 9-2. Format of Setup Data
 */
typedef struct {
	u8 bmRequestType;
	u8 bReques;
	u16 wValue;
	u16 wIndex;
	u16 wLength;
} formatSetupData;

/* Table 9-8. Standard Device Descriptor
 */
typedef struct {
	u8 bLength;
	u8 bDescriptorType;
	u16 bcdUSB;
	u8 bDeviceClass;
	u8 DeviceSubClass;
	u8 bDeviceProtocol;
	u8 bMaxPacketSize0;
	u16 idVendor;
	u16 idProduct;
	u16 bcdDevice;
	u8 iManufacturer;
	u8 iProduct;
	u8 iSerialNumber;
	u8 bNumConfigurations;
} stdDeviceDescriptor;

/* Table 9-4. Standard Request Codes
 */
#define GET_STATUS (0)
#define CLEAR_FEATURE (1)
#define SET_FEATURE (3)
#define SET_ADDRESS (5)
#define GET_DESCRIPTOR (6)
#define SET_DESCRIPTOR (7)
#define GET_CONFIGURATION (8)
#define SET_CONFIGURATION (9)
#define GET_INTERFACE (10)
#define SET_INTERFACE (11)
#define SYNCH_FRAME (12)

/* Table 9-5. Descriptor Type
 */
#define DT_DEVICE (1)
#define DT_CONFIGURATION (2)
#define DT_STRING (3)
#define DT_INTERFACE (4)
#define DT_ENDPOINT (5)
#define DT_DEVICE_QUALIFIER (6)
#define DT_OTHER_SPEED_CONFIGURATION (7)
#define DT_INTERFACE_POWER (8)

#ifdef DBG

void dbg_setup_date(u8 *buf);

#endif /* DBG */

extern const u8 deviceDescriptor[];

#endif /* _USBCORE_H_ */
