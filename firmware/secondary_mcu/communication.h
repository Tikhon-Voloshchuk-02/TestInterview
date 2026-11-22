#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdbool.h>
#include "rtc.h"

typedef enum {
	CMD_SET_TIME,
	CMD_GET_TIME,

	MSG_TIME_UPDATE,
	MSG_TIME_RESPONSE,

	MSG_SUCCESS,
	MSG_ERR,
	MSG_ACK
}msgType;


typedef struct {
	msgType type;
	DateTime time;
} Message;

bool comm_send(const Message *message);
bool comm_receive(Message *message, uint16_t timeout_ms);

void comm_wake_main(void);

#endif
