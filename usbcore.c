

#include "usbcore.h"

const UINT8 deviceDescriptor[18] =
{
	18, /* bLength */
	DT_DEVICE, /* bDescriptorType */
	 0x10,
	 0x01, /* bcdUSB 0x0110 USB 1.1; 0x0200 USB 2.0 */
	 0, /* bDeviceClass */
	 0, /* DeviceSubClass */
	 0, /* bDeviceProtocol */
	 16, /* bMaxPacketSize0 */
	 0xca,
	 0x07, /* idVendor */
	 0xaa,
	 0x55, /* idProduct */
	 0x01,
	 0x00, /* bcdDevice */
	 1, /* iManufacturer */
	 2, /* iProduct */
	 3, /* iSerialNumber */
	 1 /*bNumConfigurations */
};

#ifdef DBG
/* Table 9-2. Format of Setup Data
 */
void dbg_setup_date(UINT8 *buf)
{
	formatSetupData d;
	
	memcpy(&d, buf, 16);
	
	printf("Data transfer direction: ");
	if ((d.bmRequestType >> 7) & 0x1) printf("Device-to-host\r\n");
	else printf("Host-to-device\r\n");
	
	printf("Type: ");
	switch ((d.bmRequestType >> 5) & 0x3)
	{
		case 0:
			printf("standard\r\n");
			break;
		case 1:
			printf("class\r\n");
			break;
		case 2:
			printf("vendor\r\n");
			break;
		case 3:
		default:
			printf("reserved\r\n");
			break;
	}
	
	printf("Recipient: ");
	switch (d.bmRequestType & 0x1f)
	{
		case 0:
			printf("device\r\n");
			break;
		case 1:
			printf("interface\r\n");
			break;
		case 2:
			printf("endpoint\r\n");
			break;
		case 3:
			printf("other\r\n");
			break;
		default:
			printf("reserved\r\n");
			break;
	}
	
	printf("Specific request: %d\r\n", d.bReques); /* Table 9-4. Standard Request Codes	 */
	printf("Descriptor Type: %d; Descriptor Index: %d\r\n", d.wValue >> 8, d.wValue & 0xff);
	printf("wIndex: %d\r\n", d.wIndex);
	printf("wLength: %d\r\n", d.wLength);
}

#endif /* DBG */
