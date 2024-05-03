
#include "encoder.h"



ENCODER_ButtonState ENCODER_GetButtonState(INPUT_States *InputStates)
{
	if (InputStates->Input07 == INPUT_SET) return ENCODER_BUTTON_PUSHED;

	return ENCODER_BUTTON_RELEASED;
}



ENCODER_ABState ENCODER_GetABState(INPUT_States *InputStates)
{
	if      ((InputStates->Input05 == INPUT_RESET) && (InputStates->Input06 == INPUT_RESET)) return ENCODER_AB_00;
	else if ((InputStates->Input05 == INPUT_RESET) && (InputStates->Input06 == INPUT_SET))   return ENCODER_AB_01;
	else if ((InputStates->Input05 == INPUT_SET)   && (InputStates->Input06 == INPUT_RESET)) return ENCODER_AB_10;
	else if ((InputStates->Input05 == INPUT_SET)   && (InputStates->Input06 == INPUT_SET))   return ENCODER_AB_11;

	return ENCODER_AB_00;
}



void ENCODER_Init(ENCODER_Data *EncoderData, INPUT_States *InputStates)
{
	/* Get current states */
	EncoderData->CurrButtonState = ENCODER_GetButtonState(InputStates);
	EncoderData->CurrABState = ENCODER_GetABState(InputStates);

	/* Fill in previous states */
	EncoderData->PrevButtonState = EncoderData->CurrButtonState;
	EncoderData->PrevABState = EncoderData->CurrABState;

	/* Initialize button counter */
	EncoderData->ButtonCnt = 0;
}



ENCODER_Status ENCODER_GetCommand(ENCODER_Command *Command, ENCODER_Data *EncoderData, INPUT_States *InputStates)
{
	/* Save current states to use in new cycle */
	EncoderData->PrevButtonState = EncoderData->CurrButtonState;
	EncoderData->PrevABState = EncoderData->CurrABState;

	/* Update current states */
	EncoderData->CurrButtonState = ENCODER_GetButtonState(InputStates);
	EncoderData->CurrABState = ENCODER_GetABState(InputStates);


	/* Analyze button states and assign command */
	if (EncoderData->PrevButtonState == ENCODER_BUTTON_PUSHED)
	{
		if (EncoderData->CurrButtonState == ENCODER_BUTTON_PUSHED)
		{
			EncoderData->ButtonCnt ++;

			if ((EncoderData->ButtonCnt) == ENCODER_LONG_PUSH_DURATION)
			{
				*Command = ENCODER_CMD_LONG_PUSH;
				return ENCODER_CHANGED;
			}
		}
		else
		{
			if ((EncoderData->ButtonCnt) <= ENCODER_SHORT_PUSH_LIMIT)
			{
				*Command = ENCODER_CMD_SHORT_PUSH;
				EncoderData->ButtonCnt = 0;
				return ENCODER_CHANGED;
			}

			EncoderData->ButtonCnt = 0;
		}
	}


	/* Analyze A and B signals and assign command */
	if ((EncoderData->PrevABState) == ENCODER_AB_00)
	{
		switch (EncoderData->CurrABState)
		{
		case ENCODER_AB_10:
		{
			*Command = ENCODER_CMD_CCW;
			return ENCODER_CHANGED;
		}
		break;

		case ENCODER_AB_01:
		{
			*Command = ENCODER_CMD_CW;
			return ENCODER_CHANGED;
		}
		break;

		default:;
		}
	}

	return ENCODER_NOT_CHANGED;
}
