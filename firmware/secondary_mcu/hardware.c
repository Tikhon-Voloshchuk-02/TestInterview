void hardware_init(void){
	
	led_gpio_init();

	rtc_i2c_init();
	rtc_interrupt_init();

	//here communication w main MCU
	main_comm_init();
	main_wakeup_init();
}

bool i2c_write_registers(uint8_t device_address,
			uint8_t start_register,
			const uint8_t *data,
			size_t length){
	if(data==NULL || length==0) return false;

	i2c_start();

	if(!i2c_send_address(device_address, I2C_WRITE)){goto error;}
		
	if(!i2c_send_byte(start_register)){
		goto error;
	}


	for(size_t i=0; i<length; i++){
		if(!i2c_send_byte(data[i])){
			goto error;
		}
	}

	i2c_stop();
	return true;

error:
	i2c_stop();
	return false;

	
}

bool i2c_read_registers(uint8_t device_address,
			uint8_t start_register,
			uint8_t *data,
			size_t length){

	if(data==NULL || length==0){
		return false;
	}

	i2c_start();
	if(!i2c_send_address(device_address, I2C_WRITE)){
		goto error;
	}

	if(!i2c_send_byte(start_register)){
		goto error;
	}

	i2c_repeated_start();

	if(!i2c_send_address(device_address, I2C_READ)){
		goto error;
	}
	
	for(size_t i=0; i<length; i++){
		bool ack=(i<length-1);

		if(!i2c_read_byte(&data[i], ack)) goto error;
	}

	i2c_stop();
	return true;

error:
	i2c_stop();
	return false;
}
