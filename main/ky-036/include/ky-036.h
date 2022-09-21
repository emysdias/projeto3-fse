#ifndef KY036_H
#define KY036_H

void touchRead();
void touchHandle(void *);
extern int touch;
#define TOUCH_GPIO 23 // PINO DIGITAL UTILIZADO PELO SENSOR:  "D4" - ESP32

#endif