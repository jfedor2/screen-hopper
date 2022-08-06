#include "hardware/gpio.h"

#include "pico/stdio.h"
#include "stdio.h"

#include "crc.h"
#include "serial.h"

#define SERIAL_BAUDRATE 4000000
#define SERIAL_TX_PIN 0
#define SERIAL_RX_PIN 1
#define SERIAL_CTS_PIN 2
#define SERIAL_RTS_PIN 3

void serial_init() {
    uart_init(SERIAL_UART, SERIAL_BAUDRATE);
    uart_set_hw_flow(SERIAL_UART, true, true);
    uart_set_translate_crlf(SERIAL_UART, false);
    gpio_set_function(SERIAL_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SERIAL_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SERIAL_CTS_PIN, GPIO_FUNC_UART);
    gpio_set_function(SERIAL_RTS_PIN, GPIO_FUNC_UART);
}

#define END 0300     /* indicates end of packet */
#define ESC 0333     /* indicates byte stuffing */
#define ESC_END 0334 /* ESC ESC_END means END data byte */
#define ESC_ESC 0335 /* ESC ESC_ESC means ESC data byte */

bool serial_read(msg_recv_cb_t callback, uart_inst_t* uart) {
    static uint8_t buffer[SERIAL_MAX_PAYLOAD_SIZE + 32];
    static uint16_t bytes_read = 0;
    static bool escaped = false;

    while (uart_is_readable(uart)) {
        bytes_read %= sizeof(buffer);

        char c = uart_getc(uart);

        if (escaped) {
            switch (c) {
                case ESC_END:
                    buffer[bytes_read++] = END;
                    break;
                case ESC_ESC:
                    buffer[bytes_read++] = ESC;
                    break;
                default:
                    // this shouldn't happen
                    buffer[bytes_read++] = c;
                    break;
            }
            escaped = false;
        } else {
            switch (c) {
                case END:
                    if (bytes_read > 4) {
                        uint32_t crc = crc32(buffer, bytes_read - 4);
                        uint32_t received_crc = 0;
                        for (int i = 0; i < 4; i++) {
                            received_crc = (received_crc << 8) | buffer[bytes_read - 1 - i];
                        }
                        if (crc == received_crc) {
                            callback(buffer, bytes_read - 4);
                            bytes_read = 0;
                            return true;
                        } else {
                            printf("CRC error\n");
                        }
                    }
                    bytes_read = 0;
                    break;
                case ESC:
                    escaped = true;
                    break;
                default:
                    buffer[bytes_read++] = c;
                    break;
            }
        }
    }

    return false;
}

void send_escaped_byte(uint8_t b, uart_inst_t* uart) {
    switch (b) {
        case END:
            uart_putc_raw(uart, ESC);
            uart_putc_raw(uart, ESC_END);
            break;

        case ESC:
            uart_putc_raw(uart, ESC);
            uart_putc_raw(uart, ESC_ESC);
            break;

        default:
            uart_putc_raw(uart, b);
    }
}

void serial_write(const uint8_t* data, uint16_t len, uart_inst_t* uart) {
    uint32_t crc = crc32(data, len);

    uart_putc_raw(uart, END);

    for (int i = 0; i < len; i++) {
        send_escaped_byte(data[i], uart);
    }

    for (int i = 0; i < 4; i++) {
        send_escaped_byte((crc >> (i * 8)) & 0xFF, uart);
    }

    uart_putc_raw(uart, END);
}
