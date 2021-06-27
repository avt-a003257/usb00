#include "usbd12.h"
#include "usbcore.h"
#include "common.h"

UINT8 usbd12_read_byte(void)
{
	UINT8 retval;

	USBD12_A0 = DATA;
	USBD12_RD = 0;
	retval = USBD12_DATA;
	USBD12_RD = 1;

	return retval;
}

void usbd12_read_bytes(UINT8 len, UINT8 *buf)
{
	UINT8 i = 0;

	USBD12_A0 = DATA;
    for (i = 0; i < len; ++i)
    {
        USBD12_RD = 0;
        *(buf + i) = USBD12_DATA;
        USBD12_RD = 1;
    }
}

void usbd12_write_byte(UINT8 addr, UINT8 data)
{
	USBD12_A0 = addr;
	USBD12_WR = 0;
	USBD12_DATA = data;
	USBD12_WR = 1;
	USBD12_DATA = 0xFF;
}

void usbd12_write_bytes(UINT8 len, UINT8 *buf)
{
	UINT8 i = 0;

	USBD12_A0 = DATA;
    for (i = 0; i < len; ++i)
    {
        USBD12_WR = 0;
        USBD12_DATA = *(buf + i);
        USBD12_WR = 1;
    }
}

UINT16 usbd12_read_id(void)
{
	UINT16 retval = 0;

	usbd12_write_byte(CMD, READ_ID);
	retval = usbd12_read_byte();
	retval |= ((UINT16)usbd12_read_byte()) << 8;

	return retval;
}

#if 0
void usbd12_is_plugin(UINT8 is_plugin)
{
	usbd12_write_byte(CMD, SET_MODE);

	if (is_plugin) {
		usbd12_write_byte(DATA,
				  MODE_NON_ISO | BUS_CONN |
				  INTMOD_OK | CLOCK_RUNNING |
				  SET_LAZYCLK);
		usbd12_write_byte(DATA, DMA_RDWR | CLK_DIV);

	} else {
		usbd12_write_byte(DATA,
				  MODE_NON_ISO | BUS_DISCONN |
				  INTMOD_OK | CLOCK_RUNNING |
				  SET_LAZYCLK);
		usbd12_write_byte(DATA, DMA_RDWR | CLK_DIV);
		delayms(1000); // delay 1s
	}
}

//void usbd12_isr_handler(void *arg)
void usbd12_isr_handler(void)
{
//	UINT8 val = ((struct _isr_status *)arg)->usbd12_intreg[0];
	UINT8 val = 0;
	UINT8 buf[16] = {0};

	usbd12_write_byte(CMD, READ_INT_REG);
	g_isr.usbd12_intreg[0] = usbd12_read_byte();
	g_isr.usbd12_intreg[1] = usbd12_read_byte();

   	val = g_isr.usbd12_intreg[0];
	//printf("val=%d\r\n", val);
	if (val & SUSPEND_CHANGE)
    {
		//TODO
		printf("SUSPEND_CHANGE\r\n");
	}

	if (val & BUS_RESET)
    {
		printf("BUS_RESET\r\n");
		usbd12_is_plugin(TRUE);
	}

	if (val & EP2_IN)
    {
		//TODO
		printf("EP2_IN\r\n");
	}

	if (val & EP2_OUT)
    {
		//TODO
		printf("EP2_OUT\r\n");
	}

	if (val & EP1_IN)
    {
		printf("EP1_IN\r\n");
	}

	if (val & EP1_OUT)
    {
		printf("EP1_OUT\r\n");
	}

	if (val & EP0_IN)
    {
		printf("EP0_IN\r\n");
		usbd12_ep0_in();
	}

	if (val & EP0_OUT)
    {
		printf("EP0_OUT\r\n");
		if (usbd12_read_ep_last_status(EP_CTRL_OUT) & 0x20) /* setup */
        {
            usbd12_read_ep_buffer(EP_CTRL_OUT, 16, buf);
            d12_acknowledge_setup();
            d12_clear_buffer();
        }
        else
        {
            usbd12_read_ep_buffer(EP_CTRL_OUT, 16, buf);
            d12_clear_buffer();
        }

		dbg_setup_date(buf);
	}

//	((struct _isr_status *)arg)->usbd12_intreg[0] = 0;
}

UINT8 usbd12_read_ep_buffer(UINT8 ep, UINT8 len, UINT8 *buf)
{
    UINT8 i, j;

    usbd12_select_ep(ep);
    usbd12_write_byte(CMD, READ_BUFFER);
    usbd12_read_byte(); //byte 0: reserved; can have any value
    j = usbd12_read_byte(); //byte 1: number/length of data bytes
    if (j > len)
    {
        j = len;
    }

    dbg("ep:%d buflen:%d\r\n", ep / 2, j);
    usbd12_read_bytes(len, buf);

#ifdef DBG
    for (i = 0; i < j; ++i)
    {
        printf("%02x ", buf[i]);
    }
    printf("\r\n");
#endif

    return j;
}

UINT8 usbd12_read_ep_last_status(UINT8 ep)
{
    usbd12_write_byte(CMD, 0x40 + ep);

    return usbd12_read_byte();
}

void d12_acknowledge_setup(void)
{
    usbd12_select_ep(EP_CTRL_IN);
    usbd12_write_byte(CMD, ACKNOWLEDGE_SETUP);
    usbd12_select_ep(EP_CTRL_OUT);
    usbd12_write_byte(CMD, ACKNOWLEDGE_SETUP);
}

void d12_write_endpoint_buffer(UINT8 endp, UINT8 len, UINT8 *buf)
{
	UINT8 i;

	usbd12_select_ep(endp);
	usbd12_write_byte(CMD, WRITE_BUFFER);
	usbd12_write_byte(DATA, 0);
	usbd12_write_byte(DATA, len);

	USBD12_A0 = DATA;
	for (i = 0; i < len; ++i)
	{
		USBD12_WR = 0;
	    USBD12_DATA = *(buf + i);
	    USBD12_WR = 1;
	}

	USBD12_DATA = 0xff;
	usbd12_write_byte(CMD, VALIDATE_BUFFER);
}

static UINT16 sendLength;
static UINT8 *pSendData;
static UINT8 needZeroPacket;

void ep0_send_data(UINT8 *buf)
{
	stdDeviceDescriptor *p = (stdDeviceDescriptor *) buf;

	if (sendLength > p->bMaxPacketSize0)
	{
		d12_write_endpoint_buffer(EP_CTRL_IN, p->bMaxPacketSize0, pSendData);
		sendLength -= p->bMaxPacketSize0;
		pSendData += p->bMaxPacketSize0;
	}
	else
	{
		if (sendLength)
		{
			d12_write_endpoint_buffer(EP_CTRL_IN, sendLength, pSendData);
			sendLength = 0;
		}
		else
		{
			if (needZeroPacket)
			{
				d12_write_endpoint_buffer(EP_CTRL_IN, sendLength, pSendData);
				needZeroPacket = 0;
			}
		}
	}
}

void usbd12_ep0_in(void)
{
	usbd12_read_ep_last_status(EP_CTRL_IN);
	ep0_send_data(deviceDescriptor);
}
#endif