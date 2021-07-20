/** PDIUSBD12 chip
 */
#ifndef _USBD12_H_
#define _USBD12_H_

#include "common.h"

#define USBD12_DATA P0
#define USBD12_A0 P3_5
#define USBD12_WR P3_6
#define USBD12_RD P3_7
#define USBD12_INT P3_2

#define CMD 1
#define DATA 0

/* 11.2 initialization commands */
#define SET_ADDR_EN (0xD0)
#define SET_EP_EN (0xD8)

#define SET_MODE (0xF3)
#define MODE_NON_ISO (0 << 6)
#define MODE_ISO_OUT (1 << 6)
#define MODE_ISO_IN (2 << 6)
#define MODE_ISO_IO (3 << 6)
#define BUS_CONN (1 << 4)
#define BUS_DISCONN (0 << 4)
#define INTMOD_NAK (1 << 3)
#define INTMOD_OK (0 << 3)
#define CLOCK_RUNNING (1 << 2)
#define CLOCK_STOP (0 << 2)
#define SET_LAZYCLK (1 << 1)
#define CLR_LAZYCLK (0 << 1)

#define SOF_ONLY_INT_MODE (1 << 7)
#define DMA_RDWR (1 << 6)
#define CLK_DIV (7)

#define SET_DMA (0xFB)

/* 11.3 data flow commands */
#define READ_INT_REG (0xF4) /* this command can get 2 bytes in response */
#define SUSPEND_CHANGE (1 << 7)
#define BUS_RESET (1 << 6)
#define EP2_IN (1 << 5)
#define EP2_OUT (1 << 4)
#define EP1_IN (1 << 3)
#define EP1_OUT (1 << 2)
#define EP0_IN (1 << 1)
#define EP0_OUT (1 << 0)
#define DMA_EOT (1 << 0)

#define usbd12_select_ep(x) usbd12_write_byte(CMD, x)
#define EP_CTRL_OUT    (0x00)
#define EP_CTRL_IN    (0x01)
#define EP_1_OUT    (0x02)
#define EP_1_IN    (0x03)
#define EP_2_OUT    (0x04)
#define EP_2_IN    (0x05)

/* TODO
 * #define READ_EP_STATUS ()
 * 0x80 to 0x85
 */

u8 usbd12_read_ep_last_status(u8 ep);

#define READ_LAST_TRANSACT_STATUS_REG (0x40) /* 0x40 to 0x45 */
#define READ_BUFFER (0xF0)
#define WRITE_BUFFER (0xF0)
#define CLEAR_BUFFER (0xF2)
#define VALIDATE_BUFFER (0xFA)
/* TODO
 * #define SET_ENDPOINT_STATUS ()
 * 0x40 to 0x45
 */
#define ACKNOWLEDGE_SETUP (0xF1)

/* 11.4 general commands */
#define SEND_RESUME (0xF6)
#define READ_CURR_FRAME_NUMBER (0xF5)
#define READ_ID (0xFD)

u8 usbd12_read_byte(void);
void usbd12_write_byte(u8 type, u8 cmd);
u16 usbd12_read_id(void);
void usbd12_bus_change(void);
void usbd12_bus_reset(void);
void usbd12_ep2_in(void);
void usbd12_ep2_out(void);
void usbd12_ep1_in(void);
void usbd12_ep1_out(void);
void usbd12_ep0_in(void);
void usbd12_ep0_out(void);
void usbd12_is_plugin(bool is_plugin);
//void usbd12_isr_handler(void *arg);
void usbd12_isr_handler(void);
u8 usbd12_read_ep_buffer(u8 ep, u8 len, u8 *buf);
#define d12_clear_buffer() usbd12_write_byte(CMD, CLEAR_BUFFER)
void d12_acknowledge_setup(void);
void d12_write_endpoint_buffer(u8 endp, u8 len, u8 *buf);

#endif /* _USBUSBD12_H_ */

