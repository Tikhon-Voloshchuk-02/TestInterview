#include <stdio.h>
#include "hardware.h"

#include "led.h"
#include "communication.h"


//set_time command

static void handle_set_time(const Message *rqst){
	
	Message response = {0};

	if(rtc_set_time(&rqst->time) && rtc_start_timer(600)){
		response.type=MSG_SUCCESS;
	} else {
		response.type=MSG_ERR;
	}
	comm_send(&response);
}

static void handle_get_time(void){
	Message response = {0};

	if(rtc_get_time(&response.time)) {
		response.type=MSG_TIME_RESPONSE;
	} else{
		response.type=MST_ERR;
	}
	comm_send(&response);
}

static void handle_rtc_interrupt(void) {
	led_blink();

	Message update = {0};
	if(!rtc_get_time(&update.time)) return;

	comm_wake_main();

	//wait for READY-status
	
	if(!comm_receive(&response,1000) || response.type != MSG_READY) return;

	if(!comm_send(&update)) return;
	if(!comm_receive(&response, 1000) || response.type != MSG_ACK) return;


}

int main(void) {
	hardware_init();

	while(1){
		Message request = {0};

		if(comm_receive(&request,, 100)){
			switch(request.type){
				case CMD_SET_TIME;
					handle_set_time(&request);
					break;
				case CMD_GET_TIME;
					handle_get_time();
					break;

				default:
					break;

			}
		}

		if(rtc_interrupt_pending()){
			 rtc_clear_interrupt();

			 handle_rtc_interrupt();
		}

		enter_sleep_mod();
	}
}
