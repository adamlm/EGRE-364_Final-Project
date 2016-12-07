#ifndef distance_sensor_h
#define distance_sensor_h

#include <stdint.h>

void distance_sensor_init(void);
uint16_t distance_read(void);

#endif
