#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_on(void);
void led_off(void);

void led_blink(uint1l6_t duration_ms);

#endif
