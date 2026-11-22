#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <stdbool.h>


typdef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;

	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} DateTime;


bool rtc_set_time(const DateTime *time);

bool rtc_get_time(DateTime *time);

bool rtc_start_timer(uint16_t interval_seconds);

#endif
