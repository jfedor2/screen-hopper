#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#define BOARD_HOST_RHPORT_NUM 0
#define BOARD_HOST_RHPORT_SPEED OPT_MODE_FULL_SPEED
#define CFG_TUSB_RHPORT0_MODE (OPT_MODE_HOST | BOARD_HOST_RHPORT_SPEED)

#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN __attribute__((aligned(4)))

#define CFG_TUH_ENUMERATION_BUFSIZE 512

#define CFG_TUH_HUB 1
#define CFG_TUH_CDC 0
#define CFG_TUH_HID 16
#define CFG_TUH_MSC 0
#define CFG_TUH_VENDOR 0

#define CFG_TUH_DEVICE_MAX 16

#define CFG_TUH_HID_EPIN_BUFSIZE 64
#define CFG_TUH_HID_EPOUT_BUFSIZE 64

// we don't want tinyusb to initialize any of the UARTs for stdio
#undef PICO_DEFAULT_UART

#endif
