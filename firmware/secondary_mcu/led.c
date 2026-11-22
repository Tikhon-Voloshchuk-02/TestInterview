#include "led.h"
#include "hardware.h"

void len_on(void) { gpio_write(LED_PIN, GPIO_HIGH);}

void led_off(void) { gpio_write(LED_PIN, GPIO_LOW);}

void led_blink(uint16_t duration_ms) {
	len_on();
	delay_ms(duration_ms);

	led_off();
}
