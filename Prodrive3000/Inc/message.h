
#include "string.h"



#ifndef __message_h
#define __message_h

/* Message ID */
typedef enum
{
	MESSAGE_01,
	MESSAGE_02,
	MESSAGE_03,
	MESSAGE_04,
	MESSAGE_05,
	MESSAGE_06,
	MESSAGE_07,
	MESSAGE_08,
	MESSAGE_09,
	MESSAGE_10,
	MESSAGE_11,
	MESSAGE_12,
	MESSAGE_13,
	MESSAGE_14,
	MESSAGE_15,
	MESSAGE_16,
	MESSAGE_17,
	MESSAGE_18,
	MESSAGE_19,
	MESSAGE_20,
	MESSAGE_21,
	MESSAGE_22,
	MESSAGE_23,
	MESSAGE_24,
	MESSAGE_25,
	MESSAGE_26,
	MESSAGE_27,
	MESSAGE_28,
	MESSAGE_29,
	MESSAGE_30
} MESSAGE_ID;

/* Get message line */
void MESSAGE_GetLine(MESSAGE_ID ID, char line[24]);

#endif /* __message_h */

/* end of message.h */
