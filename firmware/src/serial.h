#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdint.h>

#include "hardware/uart.h"

#define SERIAL_MAX_PAYLOAD_SIZE 512
#define SERIAL_UART uart0

#define FORWARDER_BAUDRATE 1000000

typedef void (*msg_recv_cb_t)(const uint8_t* data, uint16_t len);

void serial_init();
bool serial_read(msg_recv_cb_t callback, uart_inst_t* uart = SERIAL_UART);
void serial_write(const uint8_t* data, uint16_t len, uart_inst_t* uart = SERIAL_UART);

#endif
