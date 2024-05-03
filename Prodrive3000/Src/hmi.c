
#include "hmi.h"



uint32_t HMI_GetInitialSpeed(SETTING_Values *SettingValues)
{
	uint16_t highSpeed, presetSpeed2;
	uint16_t speed;

	highSpeed =    (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 4, SettingValues);
	presetSpeed2 = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 6, SettingValues);

	speed = presetSpeed2;

	if (speed > highSpeed) speed = highSpeed;

	return speed;
}



void HMI_Init(HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget)
{
	HMI_ControlLocation ControlLocation = HMI_LOCAL_CTRL;
	uint16_t speed = 0;
	int16_t controlLocationSetting = 0;

	/* Initialize speed */
	speed = (uint16_t)HMI_GetInitialSpeed(SettingValues);

	/* Initialize control location */
	controlLocationSetting = SETTING_GetValue(SETTING_ARRAY_01, 15, SettingValues);
	if (controlLocationSetting == 1) ControlLocation = HMI_REMOTE_CTRL;

	/* Initialize HMI status */
	HMIStatus->DriveState = HMI_DRIVE_OK;
	HMIStatus->SettingStatus = HMI_SETTING_CHANGED;
	HMIStatus->ControlLocation = ControlLocation;
	HMIStatus->SetupMode = HMI_WORK;
	HMIStatus->MenuMode = HMI_SELECT;
	HMIStatus->ScreenType = HMI_INITIAL_SCREEN;
	HMIStatus->MenuItemID = MENU_ITEM_01;
	HMIStatus->MessageID = MESSAGE_01;
	HMIStatus->CursorPosition = HMI_CURSOR_IN_LINE1;
	HMIStatus->BeaconState = HMI_BEACON_ON;
	HMIStatus->beaconCnt = 0;
	HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
	HMIStatus->MotorUpdate = HMI_UPDATE_NOT_REQUIRED;
	HMIStatus->speed = speed;
	HMIStatus->motorDataCnt = 0;
	HMIStatus->displayCnt = 0;
	HMIStatus->motorDataPeriod = PERIOD_CONF_MOTOR_DATA_HANDLING_MS / PERIOD_CONF_HMI_TASK_MS;
	HMIStatus->displayPeriod   = PERIOD_CONF_DISPLAY_UPDATING_MS / PERIOD_CONF_HMI_TASK_MS;

	/* Initialize motor target */
	MotorTarget->Mode = MOTOR_STOP_FAST;
	MotorTarget->speed = ((float)speed) * 0.1;
	MotorTarget->accTime = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 1, SettingValues);
	MotorTarget->decTime = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 2, SettingValues);
}



void HMI_IncreaseSpeed(HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget)
{
	uint16_t highSpeed, step;
	uint16_t currSpeed, newSpeed;

	highSpeed = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 4, SettingValues);
	step = (uint16_t)HMI_SPEED_STEP;

	currSpeed = HMIStatus->speed;

	if (currSpeed <= (highSpeed - step))
	{
		newSpeed = currSpeed + step;

		HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
		HMIStatus->MotorUpdate = HMI_UPDATE_REQUIRED;

		HMIStatus->speed = newSpeed;
		MotorTarget->speed = ((float)newSpeed) * 0.1;
	}
}



void HMI_DecreaseSpeed(HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget)
{
	uint16_t lowSpeed, step;
	uint16_t currSpeed, newSpeed;

	lowSpeed = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 3, SettingValues);
	step = (uint16_t)HMI_SPEED_STEP;

	currSpeed = HMIStatus->speed;

	if (currSpeed >= (lowSpeed + step))
	{
		newSpeed = currSpeed - step;

		HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
		HMIStatus->MotorUpdate = HMI_UPDATE_REQUIRED;

		HMIStatus->speed = newSpeed;
		MotorTarget->speed = ((float)newSpeed) * 0.1;
	}
}



void HMI_SetSpeed1(HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget)
{
	int16_t highSpeed, lowSpeed, speed1;

	lowSpeed =  (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 3, SettingValues);
	highSpeed = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 4, SettingValues);
	speed1 =    (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 5, SettingValues);

	if (speed1 <= highSpeed)
	{
		if (speed1 >= lowSpeed)
		{
			HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
			HMIStatus->MotorUpdate = HMI_UPDATE_REQUIRED;

			HMIStatus->speed = speed1;
			MotorTarget->speed = ((float)speed1) * 0.1;
		}
	}
}



void HMI_SetSpeed2(HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget)
{
	int16_t highSpeed, lowSpeed, speed2;

	lowSpeed =  (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 3, SettingValues);
	highSpeed = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 4, SettingValues);
	speed2 =    (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 6, SettingValues);

	if (speed2 <= highSpeed)
	{
		if (speed2 >= lowSpeed)
		{
			HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
			HMIStatus->MotorUpdate = HMI_UPDATE_REQUIRED;

			HMIStatus->speed = speed2;
			MotorTarget->speed = ((float)speed2) * 0.1;
		}
	}
}



void HMI_OpenInitial(HMI_Status *HMIStatus)
{
	HMIStatus->SetupMode = HMI_WORK;
	HMIStatus->MenuMode = HMI_SELECT;
	HMIStatus->ScreenType = HMI_INITIAL_SCREEN;
	HMIStatus->MenuItemID = MENU_ITEM_01;
	HMIStatus->MessageID = MESSAGE_01;
	HMIStatus->CursorPosition = HMI_CURSOR_IN_LINE1;
	HMIStatus->BeaconState = HMI_BEACON_ON;
	HMIStatus->beaconCnt = 0;
	HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
}



void HMI_SwitchToFailure(HMI_Status *HMIStatus, MESSAGE_ID MessageID)
{
	HMIStatus->DriveState = HMI_DRIVE_FAILURE;
	HMIStatus->ScreenType = HMI_MESSAGE_SCREEN;
	HMIStatus->MessageID = MessageID;
	HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
}



void HMI_OpenSensorsMenu(HMI_Status *HMIStatus, MENU_ItemID MenuItemID)
{
	HMIStatus->SetupMode = HMI_WORK;
	HMIStatus->MenuMode = HMI_SELECT;
	HMIStatus->ScreenType = HMI_MENU_SCREEN;
	HMIStatus->MenuItemID = MenuItemID;
	HMIStatus->CursorPosition = HMI_CURSOR_IN_LINE1;
	HMIStatus->BeaconState = HMI_BEACON_ON;
	HMIStatus->beaconCnt = 0;
	HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
}



void HMI_OpenSetupMenu(HMI_Status *HMIStatus, MENU_ItemID MenuItemID)
{
	HMIStatus->SetupMode = HMI_SETUP;
	HMIStatus->MenuMode = HMI_SELECT;
	HMIStatus->ScreenType = HMI_MENU_SCREEN;
	HMIStatus->MenuItemID = MenuItemID;
	HMIStatus->CursorPosition = HMI_CURSOR_IN_LINE1;
	HMIStatus->BeaconState = HMI_BEACON_ON;
	HMIStatus->beaconCnt = 0;
	HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;
}



void HMI_HandleButtons(BUTTON_Command Command, HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget)
{
	HMIStatus->MotorUpdate = HMI_UPDATE_REQUIRED;

	switch (Command)
	{
	case BUTTON_CMD_STOP_FAST: MotorTarget->Mode = MOTOR_STOP_FAST; break;

	case BUTTON_CMD_STOP_SLOW: MotorTarget->Mode = MOTOR_STOP_SLOW; break;

	case BUTTON_CMD_STOP_FREERUN: MotorTarget->Mode = MOTOR_STOP_FREERUN; break;

	case BUTTON_CMD_RUN_FORWARD: MotorTarget->Mode = MOTOR_RUN_FORWARD; break;

	case BUTTON_CMD_RUN_REVERSE: MotorTarget->Mode = MOTOR_RUN_REVERSE; break;

	case BUTTON_CMD_INCREASE_SPEED: HMI_IncreaseSpeed(HMIStatus, SettingValues, MotorTarget); break;

	case BUTTON_CMD_DECREASE_SPEED: HMI_DecreaseSpeed(HMIStatus, SettingValues, MotorTarget); break;

	case BUTTON_CMD_SET_SPEED1: HMI_SetSpeed1(HMIStatus, SettingValues, MotorTarget); break;

	case BUTTON_CMD_SET_SPEED2: HMI_SetSpeed2(HMIStatus, SettingValues, MotorTarget); break;

	default:;
	}
}



void HMI_HandleEncoder(ENCODER_Command Command, HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Data MotorData, MOTOR_Target *MotorTarget)
{
	HAL_StatusTypeDef HALStatus = HAL_ERROR;
	MENU_ItemType MenuItemType;
	SETTING_ArrayID SettingArrayID;
	uint8_t selectedLine, lastLine;

	MenuItemType = MENU_GetItemType(HMIStatus->MenuItemID);
	SettingArrayID = MENU_GetSettingArrayID(HMIStatus->MenuItemID);
	selectedLine = HMIStatus->CursorPosition;
	lastLine = MENU_GetLastLine(HMIStatus->MenuItemID);

	HMIStatus->DisplayUpdate = HMI_UPDATE_REQUIRED;

	switch(HMIStatus->ScreenType)
	{
	case HMI_INITIAL_SCREEN:
	{
		switch (Command)
		{
		case ENCODER_CMD_SHORT_PUSH:
		{
			/* Open sensors menu */
			HMI_OpenSensorsMenu(HMIStatus, MENU_ITEM_01);
		}
		break;

		case ENCODER_CMD_LONG_PUSH:
		{
			/* If motor stopped open setup menu */
			if (MotorData.MotorRotation == MOTOR_STOPPED) HMI_OpenSetupMenu(HMIStatus, MENU_ITEM_02);
		}
		break;

		case ENCODER_CMD_CW:
		{
			/* If local control increase speed */
			if (HMIStatus->ControlLocation == HMI_LOCAL_CTRL) HMI_IncreaseSpeed(HMIStatus, SettingValues, MotorTarget);
		}
		break;

		case ENCODER_CMD_CCW:
		{
			/* If local control decrease speed */
			if (HMIStatus->ControlLocation == HMI_LOCAL_CTRL) HMI_DecreaseSpeed(HMIStatus, SettingValues, MotorTarget);
		}
		break;
		}
	}
	break;

	case HMI_MENU_SCREEN:
	{
		switch (HMIStatus->MenuMode)
		{
		case HMI_SELECT:
		{
			switch (Command)
			{
			case ENCODER_CMD_SHORT_PUSH:
			{
				/* Change menu mode or exit from menu */
				if (selectedLine == lastLine) HMI_OpenInitial(HMIStatus);
				else HMIStatus->MenuMode = HMI_WATCH;
			}
			break;

			case ENCODER_CMD_CW:
			{
				/* Increase cursor position */
				if (selectedLine < lastLine) (HMIStatus->CursorPosition)++;
			}
			break;

			case ENCODER_CMD_CCW:
			{
				/* Decrease cursor position */
				if (selectedLine > 1)        (HMIStatus->CursorPosition)--;
			}
			break;

			default:;
			}
		}
		break;

		case HMI_WATCH:
		{
			switch (Command)
			{
			case ENCODER_CMD_SHORT_PUSH:
			{
				/* Change menu mode */
				HMIStatus->MenuMode = HMI_SELECT;
			}
			break;

			case ENCODER_CMD_LONG_PUSH:
			{
				/* Change menu mode */
				if (MenuItemType == MENU_SETTINGS_ITEM) HMIStatus->MenuMode = HMI_CHANGE;
			}
			break;

			default:;
			}
		}
		break;

		case HMI_CHANGE:
		{
			switch (Command)
			{

			case ENCODER_CMD_SHORT_PUSH:
			{
				/* Save settings in FLASH */
				HALStatus = SETTING_Save(SettingValues);

				/* If there is error switch to failure state */
				if (HALStatus != HAL_OK)
				{
					HMI_SwitchToFailure(HMIStatus, MESSAGE_22);
					return;
				}

				/* Update setting values */
				SETTING_Load(SettingValues);
				HMIStatus->SettingStatus = HMI_SETTING_CHANGED;
				HMIStatus->MotorUpdate = HMI_UPDATE_REQUIRED;
				HMIStatus->MenuMode = HMI_SELECT;
			}
			break;

			case ENCODER_CMD_CW:
			{
				/* Increase setting value */
				SETTING_Increase(SettingArrayID, selectedLine, SettingValues);
			}
			break;

			case ENCODER_CMD_CCW:
			{
				/* Decrease setting value */
				SETTING_Decrease(SettingArrayID, selectedLine, SettingValues);
			}
			break;

			default:;
			}
		}
		break;
		}
	}
	break;

	default:;
	}
}



void HMI_HandleRelay(HMI_Status *Status, MOTOR_Data *MotorData, BUTTON_SafetyState SafetyState, BUTTON_LimitState FwdLimitState, BUTTON_LimitState RevLimitState, RELAY_Data *RelayData, SETTING_Values *SettingValues)
{
	int16_t tempRectifier = 0, tempInverter = 0;
	uint16_t motorTCU = 0;
	float highSpeed = 0;
	float speed1 = 0;
	float speed2 = 0;
	float currSpeed = 0;

	/* If signal is a health state turn on/off relay and return */
	if (RelayData->Signal == RELAY_HEALTH_STATE)
	{
		if (Status->DriveState == HMI_DRIVE_OK) RELAY_TurnOn(&RelayData->Position);
		else RELAY_TurnOff(&RelayData->Position);

		return;
	}

	/* Modify relay state */
	switch (RelayData->Signal)
	{
	case RELAY_MOTOR_ROTATES:

		if (MotorData->MotorRotation == MOTOR_ROTATES)
		{
			if (MotorData->MotorStopState != MOTOR_FREERUNS) RelayData->State = RELAY_ACTIVE;
			else RelayData->State = RELAY_INACTIVE;
		}
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_HIGH_SPEED:

		highSpeed = (float)SETTING_GetValue(SETTING_ARRAY_01, 4, SettingValues);
		currSpeed = (MotorData->currSpeed) * 10;

		if (currSpeed >= highSpeed) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_SPEED1:

		speed1 = (float)SETTING_GetValue(SETTING_ARRAY_01, 5, SettingValues);
		currSpeed = (MotorData->currSpeed) * 10;

		if (currSpeed >= speed1) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_SPEED2:

		speed2 = (float)SETTING_GetValue(SETTING_ARRAY_01, 6, SettingValues);
		currSpeed = (MotorData->currSpeed) * 10;

		if (currSpeed >= speed2) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_MOTOR_FORWARD:

		if (MotorData->MotorRotation == MOTOR_ROTATES)
		{
			if (MotorData->MotorDirection == MOTOR_FORWARD) RelayData->State = RELAY_ACTIVE;
			else RelayData->State = RELAY_INACTIVE;
		}
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_MOTOR_REVERSE:

		if (MotorData->MotorRotation == MOTOR_ROTATES)
		{
			if (MotorData->MotorDirection == MOTOR_REVERSE) RelayData->State = RELAY_ACTIVE;
			else RelayData->State = RELAY_INACTIVE;
		}
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_SAFETY_CONT:
		if (SafetyState == BUTTON_SAFETY_TRIPPED) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_LIMIT_CONT:

		if ((FwdLimitState == BUTTON_LIMIT_TRIPPED) || (RevLimitState == BUTTON_LIMIT_TRIPPED)) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_MOTOR_TCU:

		motorTCU = MotorData->SensorHMIValues.motorTCU;

		if (motorTCU >= PROT_CONF_MOTOR_ALARM_TCU) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	case RELAY_DRIVE_TEMPERATURE:

		tempRectifier = MotorData->SensorHMIValues.tempRectifier;
		tempInverter = MotorData->SensorHMIValues.tempInverter;

		if ((tempRectifier >= PROT_CONF_DRIVE_ALARM_TEMP) || (tempInverter >= PROT_CONF_DRIVE_ALARM_TEMP)) RelayData->State = RELAY_ACTIVE;
		else RelayData->State = RELAY_INACTIVE;
		break;

	default:;
	}

	/* Change relay position corresponding to the relay state */
	RELAY_ChangePosition(RelayData);
}

















