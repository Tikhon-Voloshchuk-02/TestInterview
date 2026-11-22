#ifndef HARDWARE_H
#define HARDWARE_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void hardware_init(void);

bool i2c_write_registers(
		uint8_t device_address,
		uint8_t start_register,
		const uint8_t *data,
		size_t length
		);


bool i2c_read_registers(
		uint8_t device_address,
		uint8_t start_register,
		uint8_t *data,
		size_t length
		);

#endif
