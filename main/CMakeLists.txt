idf_component_register(SRCS "wifi/wifi.c" "main.c" "mqtt/mqtt.c" "gpio/led.c" "parser/cJSON.c" "parser/parser.c"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
