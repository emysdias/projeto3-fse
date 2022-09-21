idf_component_register(SRCS "wifi/wifi.c" "main.c" "mqtt/mqtt.c" "gpio/led.c" "parser/cJSON.c" "parser/parser.c" "dht11/sensor_read.c" "dht11/dht11.c" "ky-036/ky-036.c"
 "ky-003/ky-003.c" "light-sleep/light-sleep.c" "energy-mode/energy_mode.c" INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
