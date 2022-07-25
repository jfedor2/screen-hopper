#include <bsp/board.h>
#include <tusb.h>

#include "hardware/gpio.h"

#include "serial.h"

#define FORWARDER_UART uart1
#define FORWARDER_RX_PIN 9

bool led_state = false;

void serial_callback(const uint8_t* data, uint16_t len) {
    tud_hid_report(data[0], data + 1, len - 1);
    board_led_write(led_state);
    led_state = !led_state;
}

void forwarder_serial_init() {
    uart_init(FORWARDER_UART, FORWARDER_BAUDRATE);
    uart_set_translate_crlf(FORWARDER_UART, false);
    gpio_set_function(FORWARDER_RX_PIN, GPIO_FUNC_UART);
}

int main() {
    board_init();
    tusb_init();
    forwarder_serial_init();

    while (true) {
        serial_read(serial_callback, FORWARDER_UART);
        tud_task();
    }

    return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
}

uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    return 0;
}
