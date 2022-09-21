#ifndef KY003_H
#define KY003_H

void proximityHallRead();
void digitalHallHandle();
#define HALL_GPIO 36 // PINO DIGITAL UTILIZADO PELO SENSOR:  "TX2" - ESP32
extern int magnetic;

#endif