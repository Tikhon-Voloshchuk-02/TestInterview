#include "communication.h"
#include "hardware.h"


/* send a msg to other processor*/
bool comm_send(const Message *msg){
	if(msg == NULL) {return false;}

	return msg_link_send(msg, sizeof(*msg));
}

bool comm_receive(Message *msg, uint16_t timeout_ms){
	//here check if msg exist
	return mcu_link_receive(msg, sizeof(*msg), timeout_ms);
}

void comm_wake_main(void){
	main_wake_signal();
}
