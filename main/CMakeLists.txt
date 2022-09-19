idf_component_register(SRCS "wifi/wifi.c" "main.c" "wifi/http_client.c" "mqtt/mqtt.c"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
