
#include "button.h"



void BUTTON_GetCurrentStates(BUTTON_States *ButtonStates, INPUT_States *InputStates)
{
	ButtonStates->CurrLocalSlowStop = BUTTON_RELEASED;
	ButtonStates->CurrLocalFwd = BUTTON_RELEASED;
	ButtonStates->CurrLocalRev = BUTTON_RELEASED;
	ButtonStates->CurrLocalFastStop = BUTTON_RELEASED;

	ButtonStates->CurrRemoteSlowStop = BUTTON_RELEASED;
	ButtonStates->CurrRemoteFwd = BUTTON_RELEASED;
	ButtonStates->CurrRemoteRev = BUTTON_RELEASED;
	ButtonStates->CurrRemoteCustom1 = BUTTON_RELEASED;
	ButtonStates->CurrRemoteCustom2 = BUTTON_RELEASED;
	ButtonStates->CurrRemoteCustom3 = BUTTON_RELEASED;


	if (InputStates->Input01 == INPUT_SET) ButtonStates->CurrLocalSlowStop = BUTTON_PUSHED;
	if (InputStates->Input02 == INPUT_SET) ButtonStates->CurrLocalFwd = BUTTON_PUSHED;
	if (InputStates->Input03 == INPUT_SET) ButtonStates->CurrLocalRev = BUTTON_PUSHED;
	if (InputStates->Input04 == INPUT_SET) ButtonStates->CurrLocalFastStop = BUTTON_PUSHED;

	if (InputStates->Input09 == INPUT_SET) ButtonStates->CurrRemoteSlowStop = BUTTON_PUSHED;
	if (InputStates->Input10 == INPUT_SET) ButtonStates->CurrRemoteFwd = BUTTON_PUSHED;
	if (InputStates->Input11 == INPUT_SET) ButtonStates->CurrRemoteRev = BUTTON_PUSHED;
	if (InputStates->Input12 == INPUT_SET) ButtonStates->CurrRemoteCustom1 = BUTTON_PUSHED;
	if (InputStates->Input13 == INPUT_SET) ButtonStates->CurrRemoteCustom2 = BUTTON_PUSHED;
	if (InputStates->Input14 == INPUT_SET) ButtonStates->CurrRemoteCustom3 = BUTTON_PUSHED;
}



void BUTTON_SaveCurrentStates(BUTTON_States *ButtonStates)
{
	ButtonStates->PrevLocalSlowStop = ButtonStates->CurrLocalSlowStop;
	ButtonStates->PrevLocalFwd = ButtonStates->CurrLocalFwd;
	ButtonStates->PrevLocalRev = ButtonStates->CurrLocalRev;
	ButtonStates->PrevLocalFastStop = ButtonStates->CurrLocalFastStop;

	ButtonStates->PrevRemoteSlowStop = ButtonStates->CurrRemoteSlowStop;
	ButtonStates->PrevRemoteFwd = ButtonStates->CurrRemoteFwd;
	ButtonStates->PrevRemoteRev = ButtonStates->CurrRemoteRev;
	ButtonStates->PrevRemoteCustom1 = ButtonStates->CurrRemoteCustom1;
	ButtonStates->PrevRemoteCustom2 = ButtonStates->CurrRemoteCustom2;
	ButtonStates->PrevRemoteCustom3 = ButtonStates->CurrRemoteCustom3;
}



void BUTTON_Init(BUTTON_States *ButtonStates, BUTTON_Counters *ButtonCounters, BUTTON_Settings *ButtonSettings, INPUT_States *InputStates, SETTING_Values *SettingValues)
{
	int16_t controlLocationSetting = 0;
	int16_t controlSchemeSetting = 0;
	int16_t function1Setting = 0;
	int16_t function2Setting = 0;
	int16_t function3Setting = 0;

	/* Initialize button settings */
	/* Initialize control location */
	controlLocationSetting = SETTING_GetValue(SETTING_ARRAY_01, 15, SettingValues);
	if (controlLocationSetting == 1) ButtonSettings->ControlLocation = BUTTON_REMOTE_CONTROL;
	else ButtonSettings->ControlLocation = BUTTON_LOCAL_CONTROL;

	/* Initialize control scheme */
	controlSchemeSetting = SETTING_GetValue(SETTING_ARRAY_01, 16, SettingValues);
	if (controlSchemeSetting == 0) ButtonSettings->ControlScheme = BUTTON_2_WIRE_CONTROL;
	else ButtonSettings->ControlScheme = BUTTON_3_WIRE_CONTROL;

	/* Initialize input functions */
	/* Get settings */
	function1Setting = SETTING_GetValue(SETTING_ARRAY_01, 17, SettingValues);
	function2Setting = SETTING_GetValue(SETTING_ARRAY_01, 18, SettingValues);
	function3Setting = SETTING_GetValue(SETTING_ARRAY_01, 19, SettingValues);

	/* Assign function 1 */
	switch (function1Setting)
	{
	case 1:  ButtonSettings->Function1 = BUTTON_FUNC_DECREASE_SPEED; break;
	case 2:  ButtonSettings->Function1 = BUTTON_FUNC_INCREASE_SPEED; break;
	case 3:  ButtonSettings->Function1 = BUTTON_FUNC_SPEED1;         break;
	case 4:  ButtonSettings->Function1 = BUTTON_FUNC_SPEED2;         break;
	case 5:  ButtonSettings->Function1 = BUTTON_FUNC_STOP_FAST;      break;
	case 6:  ButtonSettings->Function1 = BUTTON_FUNC_STOP_FREERUN;   break;
	case 7:  ButtonSettings->Function1 = BUTTON_FUNC_SAFETY_NO;      break;
	case 8:  ButtonSettings->Function1 = BUTTON_FUNC_SAFETY_NC;      break;
	case 9:  ButtonSettings->Function1 = BUTTON_FUNC_LIMIT_FWD_NO;   break;
	case 10: ButtonSettings->Function1 = BUTTON_FUNC_LIMIT_FWD_NC;   break;
	case 11: ButtonSettings->Function1 = BUTTON_FUNC_LIMIT_REV_NO;   break;
	case 12: ButtonSettings->Function1 = BUTTON_FUNC_LIMIT_REV_NC;   break;
	default: ButtonSettings->Function1 = BUTTON_NO_FUNC;
	}

	/* Assign function 2 */
	switch (function2Setting)
	{
	case 1:  ButtonSettings->Function2 = BUTTON_FUNC_DECREASE_SPEED; break;
	case 2:  ButtonSettings->Function2 = BUTTON_FUNC_INCREASE_SPEED; break;
	case 3:  ButtonSettings->Function2 = BUTTON_FUNC_SPEED1;         break;
	case 4:  ButtonSettings->Function2 = BUTTON_FUNC_SPEED2;         break;
	case 5:  ButtonSettings->Function2 = BUTTON_FUNC_STOP_FAST;      break;
	case 6:  ButtonSettings->Function2 = BUTTON_FUNC_STOP_FREERUN;   break;
	case 7:  ButtonSettings->Function2 = BUTTON_FUNC_SAFETY_NO;      break;
	case 8:  ButtonSettings->Function2 = BUTTON_FUNC_SAFETY_NC;      break;
	case 9:  ButtonSettings->Function2 = BUTTON_FUNC_LIMIT_FWD_NO;   break;
	case 10: ButtonSettings->Function2 = BUTTON_FUNC_LIMIT_FWD_NC;   break;
	case 11: ButtonSettings->Function2 = BUTTON_FUNC_LIMIT_REV_NO;   break;
	case 12: ButtonSettings->Function2 = BUTTON_FUNC_LIMIT_REV_NC;   break;
	default: ButtonSettings->Function2 = BUTTON_NO_FUNC;
	}

	/* Assign function 3 */
	switch (function3Setting)
	{
	case 1:  ButtonSettings->Function3 = BUTTON_FUNC_DECREASE_SPEED; break;
	case 2:  ButtonSettings->Function3 = BUTTON_FUNC_INCREASE_SPEED; break;
	case 3:  ButtonSettings->Function3 = BUTTON_FUNC_SPEED1;         break;
	case 4:  ButtonSettings->Function3 = BUTTON_FUNC_SPEED2;         break;
	case 5:  ButtonSettings->Function3 = BUTTON_FUNC_STOP_FAST;      break;
	case 6:  ButtonSettings->Function3 = BUTTON_FUNC_STOP_FREERUN;   break;
	case 7:  ButtonSettings->Function3 = BUTTON_FUNC_SAFETY_NO;      break;
	case 8:  ButtonSettings->Function3 = BUTTON_FUNC_SAFETY_NC;      break;
	case 9:  ButtonSettings->Function3 = BUTTON_FUNC_LIMIT_FWD_NO;   break;
	case 10: ButtonSettings->Function3 = BUTTON_FUNC_LIMIT_FWD_NC;   break;
	case 11: ButtonSettings->Function3 = BUTTON_FUNC_LIMIT_REV_NO;   break;
	case 12: ButtonSettings->Function3 = BUTTON_FUNC_LIMIT_REV_NC;   break;
	default: ButtonSettings->Function3 = BUTTON_NO_FUNC;
	}

	/* Initialize button counters */
	ButtonCounters->custom1cnt1 = 0;
	ButtonCounters->custom1cnt2 = 0;
	ButtonCounters->custom2cnt1 = 0;
	ButtonCounters->custom2cnt2 = 0;
	ButtonCounters->custom3cnt1 = 0;
	ButtonCounters->custom3cnt2 = 0;

	/* Update button current states */
	BUTTON_GetCurrentStates(ButtonStates, InputStates);

	/* Fill in previous states */
	BUTTON_SaveCurrentStates(ButtonStates);
}



void BUTTON_UpdateStates(BUTTON_States *ButtonStates, INPUT_States *InputStates)
{
	/* Save current states to use in new cycle */
	BUTTON_SaveCurrentStates(ButtonStates);

	/* Get new current states */
	BUTTON_GetCurrentStates(ButtonStates, InputStates);
}



BUTTON_RunPermission BUTTON_GetRunPermission(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings)
{
	BUTTON_ControlScheme ControlScheme = ButtonSettings->ControlScheme;
	BUTTON_Function Function1 = ButtonSettings->Function1;
	BUTTON_Function Function2 = ButtonSettings->Function2;
	BUTTON_Function Function3 = ButtonSettings->Function3;

	/* Check local FAST STOP button */
	if (ButtonStates->CurrLocalFastStop == BUTTON_PUSHED) return BUTTON_RUN_NOT_ALLOWED;

	/* Check local SLOW STOP button */
	if (ButtonStates->CurrLocalSlowStop == BUTTON_PUSHED) return BUTTON_RUN_NOT_ALLOWED;

	/* If 3-wire control scheme */
	if (ControlScheme == BUTTON_3_WIRE_CONTROL)
	{
		/* Check remote SLOW STOP button */
		if (ButtonStates->CurrRemoteSlowStop == BUTTON_PUSHED) return BUTTON_RUN_NOT_ALLOWED;
	}

	/* Check remote FAST STOP buttons, FREERUN STOP buttons, normally open safety contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_STOP_FAST) || (Function1 == BUTTON_FUNC_STOP_FREERUN) || (Function1 == BUTTON_FUNC_SAFETY_NO))
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED) return BUTTON_RUN_NOT_ALLOWED;
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_STOP_FAST) || (Function2 == BUTTON_FUNC_STOP_FREERUN) || (Function2 == BUTTON_FUNC_SAFETY_NO))
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED) return BUTTON_RUN_NOT_ALLOWED;
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_STOP_FAST) || (Function3 == BUTTON_FUNC_STOP_FREERUN) || (Function3 == BUTTON_FUNC_SAFETY_NO))
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED) return BUTTON_RUN_NOT_ALLOWED;
	}

	/* Check normally closed safety contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_SAFETY_NC))
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED) return BUTTON_RUN_NOT_ALLOWED;
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_SAFETY_NC))
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED) return BUTTON_RUN_NOT_ALLOWED;
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_SAFETY_NC))
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED) return BUTTON_RUN_NOT_ALLOWED;
	}

	return BUTTON_RUN_ALLOWED;
}



BUTTON_LimitState BUTTON_GetFwdLimitState(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings)
{
	BUTTON_Function Function1 = ButtonSettings->Function1;
	BUTTON_Function Function2 = ButtonSettings->Function2;
	BUTTON_Function Function3 = ButtonSettings->Function3;

	/* Check normally open forward limit contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_LIMIT_FWD_NO)
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_LIMIT_FWD_NO)
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_LIMIT_FWD_NO)
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Check normally closed forward limit contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_LIMIT_FWD_NC)
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_LIMIT_FWD_NC)
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_LIMIT_FWD_NC)
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED) return BUTTON_LIMIT_TRIPPED;
	}

	return BUTTON_LIMIT_RELEASED;
}



BUTTON_LimitState BUTTON_GetRevLimitState(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings)
{
	BUTTON_Function Function1 = ButtonSettings->Function1;
	BUTTON_Function Function2 = ButtonSettings->Function2;
	BUTTON_Function Function3 = ButtonSettings->Function3;

	/* Check normally open reverse limit contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_LIMIT_REV_NO)
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_LIMIT_REV_NO)
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_LIMIT_REV_NO)
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Check normally closed reverse limit contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_LIMIT_REV_NC)
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_LIMIT_REV_NC)
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED) return BUTTON_LIMIT_TRIPPED;
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_LIMIT_REV_NC)
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED) return BUTTON_LIMIT_TRIPPED;
	}

	return BUTTON_LIMIT_RELEASED;
}



BUTTON_SafetyState BUTTON_GetSafetyState(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings)
{
	BUTTON_Function Function1 = ButtonSettings->Function1;
	BUTTON_Function Function2 = ButtonSettings->Function2;
	BUTTON_Function Function3 = ButtonSettings->Function3;

	/* Check normally open safety contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_SAFETY_NO)
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED) return BUTTON_SAFETY_TRIPPED;
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_SAFETY_NO)
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED) return BUTTON_SAFETY_TRIPPED;
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_SAFETY_NO)
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED) return BUTTON_SAFETY_TRIPPED;
	}

	/* Check normally closed safety contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_SAFETY_NC)
	{
		if (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED) return BUTTON_SAFETY_TRIPPED;
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_SAFETY_NC)
	{
		if (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED) return BUTTON_SAFETY_TRIPPED;
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_SAFETY_NC)
	{
		if (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED) return BUTTON_SAFETY_TRIPPED;
	}

	return BUTTON_SAFETY_RELEASED;
}



BUTTON_Status BUTTON_GetCommand(BUTTON_Command *Command, BUTTON_States *ButtonStates, BUTTON_Counters *Counters, BUTTON_Direction Direction, BUTTON_Settings *ButtonSettings)
{
	BUTTON_ControlLocation ControlLocation = ButtonSettings->ControlLocation;
	BUTTON_ControlScheme ControlScheme = ButtonSettings->ControlScheme;
	BUTTON_Function Function1 = ButtonSettings->Function1;
	BUTTON_Function Function2 = ButtonSettings->Function2;
	BUTTON_Function Function3 = ButtonSettings->Function3;
	BUTTON_RunPermission RunPermission = BUTTON_RUN_NOT_ALLOWED;
	BUTTON_LimitState FwdLimitState = BUTTON_LIMIT_TRIPPED, RevLimitState = BUTTON_LIMIT_TRIPPED;



	/************************************************************************************************************/
	/****************************************** ASSIGN FAST STOP COMMAND ****************************************/
	/************************************************************************************************************/

	/* Check local button */
	if ((ButtonStates->PrevLocalFastStop == BUTTON_RELEASED) && (ButtonStates->CurrLocalFastStop == BUTTON_PUSHED))
	{
		*Command = BUTTON_CMD_STOP_FAST;
		return BUTTON_CHANGED;
	}

	/* Check remote buttons and normally open safety contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_STOP_FAST) || (Function1 == BUTTON_FUNC_SAFETY_NO))
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_STOP_FAST) || (Function2 == BUTTON_FUNC_SAFETY_NO))
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_STOP_FAST) || (Function3 == BUTTON_FUNC_SAFETY_NO))
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Check normally closed safety contacts */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_SAFETY_NC)
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_SAFETY_NC)
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_SAFETY_NC)
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Check normally open forward limit contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_LIMIT_FWD_NO) && (Direction == BUTTON_FORWARD))
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_LIMIT_FWD_NO) && (Direction == BUTTON_FORWARD))
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_LIMIT_FWD_NO) && (Direction == BUTTON_FORWARD))
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Check normally open reverse limit contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_LIMIT_REV_NO) && (Direction == BUTTON_REVERSE))
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_LIMIT_REV_NO) && (Direction == BUTTON_REVERSE))
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_LIMIT_REV_NO) && (Direction == BUTTON_REVERSE))
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Check normally closed forward limit contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_LIMIT_FWD_NC) && (Direction == BUTTON_FORWARD))
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_LIMIT_FWD_NC) && (Direction == BUTTON_FORWARD))
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_LIMIT_FWD_NC) && (Direction == BUTTON_FORWARD))
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Check normally closed reverse limit contacts */
	/* Input 4 */
	if ((Function1 == BUTTON_FUNC_LIMIT_REV_NC) && (Direction == BUTTON_REVERSE))
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if ((Function2 == BUTTON_FUNC_LIMIT_REV_NC) && (Direction == BUTTON_REVERSE))
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if ((Function3 == BUTTON_FUNC_LIMIT_REV_NC) && (Direction == BUTTON_REVERSE))
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_PUSHED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_FAST;
			return BUTTON_CHANGED;
		}
	}



	/************************************************************************************************************/
	/****************************************** ASSIGN SLOW STOP COMMAND ****************************************/
	/************************************************************************************************************/

	/* Check local button */
	if ((ButtonStates->PrevLocalSlowStop == BUTTON_RELEASED) && (ButtonStates->CurrLocalSlowStop == BUTTON_PUSHED))
	{
		*Command = BUTTON_CMD_STOP_SLOW;
		return BUTTON_CHANGED;
	}

	/* Check remote buttons */
	switch (ControlScheme)
	{
	/* Case 2-wire control scheme */
	case BUTTON_2_WIRE_CONTROL:
	{
		/* Check FORWARD button */
		if ((ButtonStates->PrevRemoteFwd == BUTTON_PUSHED) && (ButtonStates->CurrRemoteFwd == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_SLOW;
			return BUTTON_CHANGED;
		}

		/* Check REVERSE button */
		if ((ButtonStates->PrevRemoteRev == BUTTON_PUSHED) && (ButtonStates->CurrRemoteRev == BUTTON_RELEASED))
		{
			*Command = BUTTON_CMD_STOP_SLOW;
			return BUTTON_CHANGED;
		}
	}
	break;

	/* Case 3-wire control scheme */
	case BUTTON_3_WIRE_CONTROL:
	{
		/* Check STOP button */
		if ((ButtonStates->PrevRemoteSlowStop == BUTTON_RELEASED) && (ButtonStates->CurrRemoteSlowStop == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_SLOW;
			return BUTTON_CHANGED;
		}
	}
	break;

	default:;
	}



	/************************************************************************************************************/
	/***************************************** ASSIGN FREERUN STOP COMMAND **************************************/
	/************************************************************************************************************/

	/* Check remote buttons */
	/* Input 4 */
	if (Function1 == BUTTON_FUNC_STOP_FREERUN)
	{
		if ((ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FREERUN;
			return BUTTON_CHANGED;
		}
	}

	/* Input 5 */
	if (Function2 == BUTTON_FUNC_STOP_FREERUN)
	{
		if ((ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FREERUN;
			return BUTTON_CHANGED;
		}
	}

	/* Input 6 */
	if (Function3 == BUTTON_FUNC_STOP_FREERUN)
	{
		if ((ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED))
		{
			*Command = BUTTON_CMD_STOP_FREERUN;
			return BUTTON_CHANGED;
		}
	}



	/************************************************************************************************************/
	/************************************* ASSIGN FORWARD AND REVERSE COMMAND ***********************************/
	/************************************************************************************************************/

	switch (ControlLocation)
	{
	/* Case local control */
	case BUTTON_LOCAL_CONTROL:
	{
		/* Check FORWARD button */
		if ((ButtonStates->PrevLocalFwd == BUTTON_RELEASED) && (ButtonStates->CurrLocalFwd == BUTTON_PUSHED))
		{
			/* If button REVERSE not pushed */
			if (ButtonStates->CurrLocalRev == BUTTON_RELEASED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* Get forward limit state */
				FwdLimitState = BUTTON_GetFwdLimitState(ButtonStates, ButtonSettings);

				/* If run forward allowed */
				if ((RunPermission == BUTTON_RUN_ALLOWED) && (FwdLimitState == BUTTON_LIMIT_RELEASED))
				{
					*Command = BUTTON_CMD_RUN_FORWARD;
					return BUTTON_CHANGED;

				}
			}
		}

		/* Check REVERSE button */
		if ((ButtonStates->PrevLocalRev == BUTTON_RELEASED) && (ButtonStates->CurrLocalRev == BUTTON_PUSHED))
		{
			/* If button FORWARD not pushed */
			if (ButtonStates->CurrLocalFwd == BUTTON_RELEASED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* Get reverse limit state */
				RevLimitState = BUTTON_GetRevLimitState(ButtonStates, ButtonSettings);

				/* If run reverse allowed */
				if ((RunPermission == BUTTON_RUN_ALLOWED) && (RevLimitState == BUTTON_LIMIT_RELEASED))
				{
					*Command = BUTTON_CMD_RUN_REVERSE;
					return BUTTON_CHANGED;
				}
			}
		}
	}
	break;

	/* Case remote control */
	case BUTTON_REMOTE_CONTROL:
	{
		/* Check FORWARD button */
		if ((ButtonStates->PrevRemoteFwd == BUTTON_RELEASED) && (ButtonStates->CurrRemoteFwd == BUTTON_PUSHED))
		{
			/* If button REVERSE not pushed */
			if (ButtonStates->CurrRemoteRev == BUTTON_RELEASED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* Get forward limit state */
				FwdLimitState = BUTTON_GetFwdLimitState(ButtonStates, ButtonSettings);

				/* If run forward allowed */
				if ((RunPermission == BUTTON_RUN_ALLOWED) && (FwdLimitState == BUTTON_LIMIT_RELEASED))
				{
					*Command = BUTTON_CMD_RUN_FORWARD;
					return BUTTON_CHANGED;
				}
			}
		}

		/* Check REVERSE button */
		if ((ButtonStates->PrevRemoteRev == BUTTON_RELEASED) && (ButtonStates->CurrRemoteRev == BUTTON_PUSHED))
		{
			/* If button FORWARD not pushed */
			if (ButtonStates->CurrRemoteFwd == BUTTON_RELEASED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* Get reverse limit state */
				RevLimitState = BUTTON_GetRevLimitState(ButtonStates, ButtonSettings);

				/* If run reverse allowed */
				if ((RunPermission == BUTTON_RUN_ALLOWED) && (RevLimitState == BUTTON_LIMIT_RELEASED))
				{
					*Command = BUTTON_CMD_RUN_REVERSE;
					return BUTTON_CHANGED;
				}
			}
		}
	}
	break;

	default:;
	}



	/************************************************************************************************************/
	/*************************************** ASSIGN DECREASE SPEED COMMAND **************************************/
	/************************************************************************************************************/

	/* If remote control */
	if (ControlLocation == BUTTON_REMOTE_CONTROL)
	{
		/* Check remote buttons */
		/* Input 4 */
		if (Function1 == BUTTON_FUNC_DECREASE_SPEED)
		{
			/* If button is pushed now */
			if (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If button was released earlier */
				if (ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED)
				{
					Counters->custom1cnt1 = 0;
					Counters->custom1cnt2 = 0;

					/* If run allowed */
					if (RunPermission == BUTTON_RUN_ALLOWED)
					{
						*Command = BUTTON_CMD_DECREASE_SPEED;
						return BUTTON_CHANGED;
					}
				}

				/* If button was pushed earlier */
				else
				{
					/* If delay before the fast change first command has elapsed */
					if (Counters->custom1cnt1 >= BUTTON_DELAY_BEFORE_FAST_CHG)
					{
						/* If delay between the fast change commands has elapsed */
						if (Counters->custom1cnt2 >= BUTTON_DELAY_BETWEEN_FAST_CHG)
						{
							Counters->custom1cnt2 = 0;

							/* If run allowed */
							if (RunPermission == BUTTON_RUN_ALLOWED)
							{
								*Command = BUTTON_CMD_DECREASE_SPEED;
								return BUTTON_CHANGED;
							}
						}
						else Counters->custom1cnt2 ++;
					}
					else Counters->custom1cnt1 ++;
				}
			}
		}

		/* Input 5 */
		if (Function2 == BUTTON_FUNC_DECREASE_SPEED)
		{
			/* If button is pushed now */
			if (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If button was released earlier */
				if (ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED)
				{
					Counters->custom2cnt1 = 0;
					Counters->custom2cnt2 = 0;

					/* If run allowed */
					if (RunPermission == BUTTON_RUN_ALLOWED)
					{
						*Command = BUTTON_CMD_DECREASE_SPEED;
						return BUTTON_CHANGED;
					}
				}

				/* If button was pushed earlier */
				else
				{
					/* If delay before the fast change first command has elapsed */
					if (Counters->custom2cnt1 >= BUTTON_DELAY_BEFORE_FAST_CHG)
					{
						/* If delay between the fast change commands has elapsed */
						if (Counters->custom2cnt2 >= BUTTON_DELAY_BETWEEN_FAST_CHG)
						{
							Counters->custom2cnt2 = 0;

							/* If run allowed */
							if (RunPermission == BUTTON_RUN_ALLOWED)
							{
								*Command = BUTTON_CMD_DECREASE_SPEED;
								return BUTTON_CHANGED;
							}
						}
						else Counters->custom2cnt2 ++;
					}
					else Counters->custom2cnt1 ++;
				}
			}
		}

		/* Input 6 */
		if (Function3 == BUTTON_FUNC_DECREASE_SPEED)
		{
			/* If button is pushed now */
			if (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If button was released earlier */
				if (ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED)
				{
					Counters->custom3cnt1 = 0;
					Counters->custom3cnt2 = 0;

					/* If run allowed */
					if (RunPermission == BUTTON_RUN_ALLOWED)
					{
						*Command = BUTTON_CMD_DECREASE_SPEED;
						return BUTTON_CHANGED;
					}
				}

				/* If button was pushed earlier */
				else
				{
					/* If delay before the fast change first command has elapsed */
					if (Counters->custom3cnt1 >= BUTTON_DELAY_BEFORE_FAST_CHG)
					{
						/* If delay between the fast change commands has elapsed */
						if (Counters->custom3cnt2 >= BUTTON_DELAY_BETWEEN_FAST_CHG)
						{
							Counters->custom3cnt2 = 0;

							/* If run allowed */
							if (RunPermission == BUTTON_RUN_ALLOWED)
							{
								*Command = BUTTON_CMD_DECREASE_SPEED;
								return BUTTON_CHANGED;
							}
						}
						else Counters->custom3cnt2 ++;
					}
					else Counters->custom3cnt1 ++;
				}
			}
		}
	}



	/************************************************************************************************************/
	/*************************************** ASSIGN INCREASE SPEED COMMAND **************************************/
	/************************************************************************************************************/

	/* If remote control */
	if (ControlLocation == BUTTON_REMOTE_CONTROL)
	{
		/* Check remote buttons */
		/* Input 4 */
		if (Function1 == BUTTON_FUNC_INCREASE_SPEED)
		{
			/* If button is pushed now */
			if (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If button was released earlier */
				if (ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED)
				{
					Counters->custom1cnt1 = 0;
					Counters->custom1cnt2 = 0;

					/* If run allowed */
					if (RunPermission == BUTTON_RUN_ALLOWED)
					{
						*Command = BUTTON_CMD_INCREASE_SPEED;
						return BUTTON_CHANGED;
					}
				}

				/* If button was pushed earlier */
				else
				{
					/* If delay before the fast change first command has elapsed */
					if (Counters->custom1cnt1 >= BUTTON_DELAY_BEFORE_FAST_CHG)
					{
						/* If delay between the fast change commands has elapsed */
						if (Counters->custom1cnt2 >= BUTTON_DELAY_BETWEEN_FAST_CHG)
						{
							Counters->custom1cnt2 = 0;

							/* If run allowed */
							if (RunPermission == BUTTON_RUN_ALLOWED)
							{
								*Command = BUTTON_CMD_INCREASE_SPEED;
								return BUTTON_CHANGED;
							}
						}
						else Counters->custom1cnt2 ++;
					}
					else Counters->custom1cnt1 ++;
				}
			}
		}

		/* Input 5 */
		if (Function2 == BUTTON_FUNC_INCREASE_SPEED)
		{
			/* If button is pushed now */
			if (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If button was released earlier */
				if (ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED)
				{
					Counters->custom2cnt1 = 0;
					Counters->custom2cnt2 = 0;

					/* If run allowed */
					if (RunPermission == BUTTON_RUN_ALLOWED)
					{
						*Command = BUTTON_CMD_INCREASE_SPEED;
						return BUTTON_CHANGED;
					}
				}

				/* If button was pushed earlier */
				else
				{
					/* If delay before the fast change first command has elapsed */
					if (Counters->custom2cnt1 >= BUTTON_DELAY_BEFORE_FAST_CHG)
					{
						/* If delay between the fast change commands has elapsed */
						if (Counters->custom2cnt2 >= BUTTON_DELAY_BETWEEN_FAST_CHG)
						{
							Counters->custom2cnt2 = 0;

							/* If run allowed */
							if (RunPermission == BUTTON_RUN_ALLOWED)
							{
								*Command = BUTTON_CMD_INCREASE_SPEED;
								return BUTTON_CHANGED;
							}
						}
						else Counters->custom2cnt2 ++;
					}
					else Counters->custom2cnt1 ++;
				}
			}
		}

		/* Input 6 */
		if (Function3 == BUTTON_FUNC_INCREASE_SPEED)
		{
			/* If button is pushed now */
			if (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED)
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If button was released earlier */
				if (ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED)
				{
					Counters->custom3cnt1 = 0;
					Counters->custom3cnt2 = 0;

					/* If run allowed */
					if (RunPermission == BUTTON_RUN_ALLOWED)
					{
						*Command = BUTTON_CMD_INCREASE_SPEED;
						return BUTTON_CHANGED;
					}
				}

				/* If button was pushed earlier */
				else
				{
					/* If delay before the fast change first command has elapsed */
					if (Counters->custom3cnt1 >= BUTTON_DELAY_BEFORE_FAST_CHG)
					{
						/* If delay between the fast change commands has elapsed */
						if (Counters->custom3cnt2 >= BUTTON_DELAY_BETWEEN_FAST_CHG)
						{
							Counters->custom3cnt2 = 0;

							/* If run allowed */
							if (RunPermission == BUTTON_RUN_ALLOWED)
							{
								*Command = BUTTON_CMD_INCREASE_SPEED;
								return BUTTON_CHANGED;
							}
						}
						else Counters->custom3cnt2 ++;
					}
					else Counters->custom3cnt1 ++;
				}
			}
		}
	}



	/************************************************************************************************************/
	/***************************************** ASSIGN SET SPEED 1 COMMAND ***************************************/
	/************************************************************************************************************/

	/* If remote control */
	if (ControlLocation == BUTTON_REMOTE_CONTROL)
	{
		/* Check remote buttons */
		/* Input 4 */
		if (Function1 == BUTTON_FUNC_SPEED1)
		{
			if ((ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED))
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If run allowed */
				if (RunPermission == BUTTON_RUN_ALLOWED)
				{
					*Command = BUTTON_CMD_SET_SPEED1;
					return BUTTON_CHANGED;
				}
			}
		}

		/* Input 5 */
		if (Function2 == BUTTON_FUNC_SPEED1)
		{
			if ((ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED))
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If run allowed */
				if (RunPermission == BUTTON_RUN_ALLOWED)
				{
					*Command = BUTTON_CMD_SET_SPEED1;
					return BUTTON_CHANGED;
				}
			}
		}

		/* Input 6 */
		if (Function3 == BUTTON_FUNC_SPEED1)
		{
			if ((ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED))
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If run allowed */
				if (RunPermission == BUTTON_RUN_ALLOWED)
				{
					*Command = BUTTON_CMD_SET_SPEED1;
					return BUTTON_CHANGED;
				}
			}
		}
	}



	/************************************************************************************************************/
	/***************************************** ASSIGN SET SPEED 2 COMMAND ***************************************/
	/************************************************************************************************************/

	/* If remote control */
	if (ControlLocation == BUTTON_REMOTE_CONTROL)
	{
		/* Check remote buttons */
		/* Input 4 */
		if (Function1 == BUTTON_FUNC_SPEED2)
		{
			if ((ButtonStates->PrevRemoteCustom1 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom1 == BUTTON_PUSHED))
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If run allowed */
				if (RunPermission == BUTTON_RUN_ALLOWED)
				{
					*Command = BUTTON_CMD_SET_SPEED2;
					return BUTTON_CHANGED;
				}
			}
		}

		/* Input 5 */
		if (Function2 == BUTTON_FUNC_SPEED2)
		{
			if ((ButtonStates->PrevRemoteCustom2 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom2 == BUTTON_PUSHED))
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If run allowed */
				if (RunPermission == BUTTON_RUN_ALLOWED)
				{
					*Command = BUTTON_CMD_SET_SPEED2;
					return BUTTON_CHANGED;
				}
			}
		}

		/* Input 6 */
		if (Function3 == BUTTON_FUNC_SPEED2)
		{
			if ((ButtonStates->PrevRemoteCustom3 == BUTTON_RELEASED) && (ButtonStates->CurrRemoteCustom3 == BUTTON_PUSHED))
			{
				/* Get run permission */
				RunPermission = BUTTON_GetRunPermission(ButtonStates, ButtonSettings);

				/* If run allowed */
				if (RunPermission == BUTTON_RUN_ALLOWED)
				{
					*Command = BUTTON_CMD_SET_SPEED2;
					return BUTTON_CHANGED;
				}
			}
		}
	}

	return BUTTON_NOT_CHANGED;
}
