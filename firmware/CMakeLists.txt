cmake_minimum_required(VERSION 3.13)

add_compile_definitions(PICO_DEFAULT_UART_BAUD_RATE=921600)

set(PICO_COPY_TO_RAM 1)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
set(PICO_TINYUSB_PATH "${CMAKE_CURRENT_LIST_DIR}/tinyusb")
set(OUR_PIO_USB_PATH "${CMAKE_CURRENT_LIST_DIR}/src/pio_usb")

include(pico_sdk_import.cmake)

project(screenhopper)

pico_sdk_init()

add_compile_options(-Wall)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

add_executable(screenhopper src/remapper.cc src/remapper_single.cc ${OUR_PIO_USB_PATH}/pio_usb.c ${OUR_PIO_USB_PATH}/usb_crc.c src/crc.cc src/descriptor_parser.cc src/pio_usb_stuff.cc src/tinyusb_stuff.cc src/our_descriptor.cc src/globals.cc src/config.cc src/quirks.cc src/interval_override.cc src/serial.cc)

pico_generate_pio_header(screenhopper ${OUR_PIO_USB_PATH}/usb_tx.pio)
pico_generate_pio_header(screenhopper ${OUR_PIO_USB_PATH}/usb_rx.pio)

target_include_directories(screenhopper PRIVATE src src/tusb_config_device ${OUR_PIO_USB_PATH})

target_link_libraries(screenhopper pico_stdlib pico_multicore hardware_pio hardware_dma hardware_flash tinyusb_device tinyusb_board)

pico_add_extra_outputs(screenhopper)


add_executable(forwarder src/forwarder.cc src/our_descriptor.cc src/tinyusb_stuff.cc src/serial.cc src/crc.cc)
target_include_directories(forwarder PRIVATE src src/tusb_config_device)
target_link_libraries(forwarder pico_stdlib tinyusb_device tinyusb_board)
pico_add_extra_outputs(forwarder)

add_executable(screenhopper_a src/remapper.cc src/remapper_dual_a.cc src/crc.cc src/descriptor_parser.cc src/tinyusb_stuff.cc src/our_descriptor.cc src/globals.cc src/config.cc src/quirks.cc src/interval_override.cc src/serial.cc)
target_include_directories(screenhopper_a PRIVATE src src/tusb_config_device)
target_link_libraries(screenhopper_a pico_stdlib hardware_flash tinyusb_device tinyusb_board)
pico_add_extra_outputs(screenhopper_a)

add_executable(screenhopper_b src/remapper_dual_b.cc src/crc.cc src/interval_override.cc src/serial.cc)
target_include_directories(screenhopper_b PRIVATE src src/tusb_config_host)
target_link_libraries(screenhopper_b pico_stdlib tinyusb_host tinyusb_board)
pico_add_extra_outputs(screenhopper_b)
