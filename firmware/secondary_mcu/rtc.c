#include "rtc.h"
#include <stddef.h>

#include "hardware.h"
#define RTC_I2C_ADDRESS 0x52


// BCD-format:= 10 -> 2 format
static uint8_t dec_to_bcd(uint8_t value) {
	return ( ((value/10) <<  4) | (value%10) );
}
// BCDformat:= 3 ->10 format
static uint8_t bcd_to_dec(uint8_t value){
	return ((value >> 4)*10) + (value & 0x0F);
}

static bool is_leap_year(uint16_t year){
	return (year%4==0 && year%100 != 0) || (year%400==0);
}

static bool validate_time (const DateTime *time){
	if(time == NULL) return false;
	
	if(
		time->year < 2000 || time->year > 2099 ||
		time->month < 1 || time->month > 12 ||
		time->hours > 23 ||
		time->minutes > 59 ||
		time -> seconds > 59
	) return false;

	static const uint8_t days_in_month[12] = {31,28,31,30,31,30,
						  31,31,30,31,30,31};

	uint8_t max_day = days_in_month[time->month-1];

	//leap year =)
	if(time->month==2 && is_leap_year(time->year)) max_day=29;

	return time->day >= 1 &&
	       time->day <= max_day;
}

bool rtc_set_time(const DateTime *time){

	//convert BCD

	uint8_t time_data[3] ={
		dec_to_bcd(time->seconds),
		dec_to_bcd(time->minutes),
		dec_to_bcd(time->hours),
	};

	uint8_t date_data[3] = {
		dec_to_bcd(time->day),
		dec_to_bcd(time->month),
		dec_to_bcd(time->year%100)
	};


	//write time in registers:
	if(!i2c_write_registers(RTC_I2C_ADDRESS, 0x00, time_data, 3)){return false;}

	if(!i2c_write_registers(RTC_I2C_ADDRESS, 0x04, date_data, 3)){return false;}

	return true;
	
}

bool rtc_get_time(DateTime *time){
	if(time==NULL) return false;
	
	uint8_t time_data[3];
	uint8_t date_data[3];

	if(!i2c_read_registers(RTC_I2C_ADDRESS, 0x00, time_data, 3)){return false;}

	if(!i2c_read_registers(RTC_I2C_ADDRESS, 0x04, date_data, 3)){return false;}

	time->seconds = bcd_to_dec(time_data[0] & 0x7F);
    	time->minutes = bcd_to_dec(time_data[1] & 0x7F);
    	time->hours   = bcd_to_dec(time_data[2] & 0x3F);

    	time->day   = bcd_to_dec(date_data[0] & 0x3F);
    	time->month = bcd_to_dec(date_data[1] & 0x1F);
    	time->year  = 2000 + bcd_to_dec(date_data[2]);

	
	return validate_time(time);
}

//define timer intervall
//I'll describe what operations we could perform on the registers
bool rtc_start_timer(uint16_t interval_seconds){
	if(interval_seconds==0) return false;

	if(!rtc_timer_stop()) return false;

	if(!rtc_timer_set_value(interval_seconds)) return false;

	if(!rtc_timer_enable_repeat()) return false;

	if(!rtc_timer_enable_interrupt()) return false;
	
	return rtc_timer_start();
}



