#ifndef SENSOR_READ_H
#define SENSOR_READ_H

void readTempAndUmid();
void tempUmidData(void *);
extern int humidity;
extern int temperature;

#endif