#ifndef LED_H
#define LED_H

void gpioSetLed();
void ledPWM();
void ledHandle(void *);
extern double intensity;

#endif