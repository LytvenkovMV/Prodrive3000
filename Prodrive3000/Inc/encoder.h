
#include "input.h"



#ifndef __encoder_h
#define __encoder_h

/* Time limit of the button short push */
#define ENCODER_SHORT_PUSH_LIMIT		(200)

/* Duration of the button long push */
#define ENCODER_LONG_PUSH_DURATION		(500)

/* Encoder push button state */
typedef enum
{
	ENCODER_BUTTON_RELEASED,
	ENCODER_BUTTON_PUSHED
} ENCODER_ButtonState;

/* Encoder A and B signal state */
typedef enum
{
	ENCODER_AB_00,
	ENCODER_AB_01,
	ENCODER_AB_11,
	ENCODER_AB_10
} ENCODER_ABState;

/* Encoder data */
typedef struct
{
	ENCODER_ButtonState CurrButtonState;
	ENCODER_ButtonState PrevButtonState;
	ENCODER_ABState CurrABState;
	ENCODER_ABState PrevABState;
	uint32_t ButtonCnt;
} ENCODER_Data;

/* Encoder status */
typedef enum
{
	ENCODER_NOT_CHANGED,
	ENCODER_CHANGED
} ENCODER_Status;

/* Encoder command */
typedef enum
{
	ENCODER_CMD_SHORT_PUSH,
	ENCODER_CMD_LONG_PUSH,
	ENCODER_CMD_CW,
	ENCODER_CMD_CCW
} ENCODER_Command;

/* Initialize encoder */
void ENCODER_Init(ENCODER_Data *EncoderData, INPUT_States *InputStates);

/* Analyze current and previous input states and assign the command from encoder */
ENCODER_Status ENCODER_GetCommand(ENCODER_Command *Command, ENCODER_Data *EncoderData, INPUT_States *InputStates);

#endif /* __encoder_h */

/* end of encoder.h */
