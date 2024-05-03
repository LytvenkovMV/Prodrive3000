
#include "relay.h"



void RELAY_Init(RELAY_Data *Data, SETTING_Values *SettingValues, uint16_t period_ms)
{
	RELAY_Signal Signal = RELAY_NO_SIGNAL;
	RELAY_Mode Mode = RELAY_POSITIVE_MODE;
	int16_t signalSetting = 0;
	int16_t modeSetting = 0;
	uint16_t timeSetting = 0;
	uint32_t time = 0;

	signalSetting = SETTING_GetValue(SETTING_ARRAY_01, 20, SettingValues);
	modeSetting = SETTING_GetValue(SETTING_ARRAY_01, 22, SettingValues);
	timeSetting = SETTING_GetValue(SETTING_ARRAY_01, 21, SettingValues);

	switch (signalSetting)
	{
	case 1:  Signal = RELAY_HEALTH_STATE;      break;
	case 2:  Signal = RELAY_MOTOR_ROTATES;     break;
	case 3:  Signal = RELAY_HIGH_SPEED;        break;
	case 4:  Signal = RELAY_SPEED1;            break;
	case 5:  Signal = RELAY_SPEED2;            break;
	case 6:  Signal = RELAY_MOTOR_FORWARD;     break;
	case 7:  Signal = RELAY_MOTOR_REVERSE;     break;
	case 8:  Signal = RELAY_SAFETY_CONT;       break;
	case 9:  Signal = RELAY_LIMIT_CONT;        break;
	case 10: Signal = RELAY_MOTOR_TCU;         break;
	case 11: Signal = RELAY_DRIVE_TEMPERATURE; break;
	default: Signal = RELAY_NO_SIGNAL;
	}

	if (modeSetting == 1) Mode = RELAY_NEGATIVE_MODE;

	time = 100 * timeSetting / period_ms;

	Data->Signal = Signal;
	Data->Mode = Mode;
	Data->State = RELAY_INACTIVE;
	Data->Position = RELAY_OFF;
	Data->cnt = 0;
	Data->time = time;

	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
}



void RELAY_TurnOn(RELAY_Position *Position)
{
	if (*Position != RELAY_ON)
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
		*Position = RELAY_ON;
	}
}



void RELAY_TurnOff(RELAY_Position *Position)
{
	if (*Position != RELAY_OFF)
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
		*Position = RELAY_OFF;
	}
}



void RELAY_ChangePosition(RELAY_Data *Data)
{
	switch (Data->State)
	{
	/* Case relay active */
	case RELAY_ACTIVE:

		switch (Data->Mode)
		{
		/* Case positive mode */
		case RELAY_POSITIVE_MODE:
			/* If relay isn't in on position */
			if (Data->Position != RELAY_ON)
			{
				/* If time has elapsed turn on relay */
				if (Data->cnt >= Data->time)
				{
					Data->cnt = 0;
					Data->Position = RELAY_ON;
					HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
				}
				else Data->cnt ++;
			}
			break;

		/* Case negative mode */
		case RELAY_NEGATIVE_MODE:
			/* If relay isn't in off position */
			if (Data->Position != RELAY_OFF)
			{
				/* If time has elapsed turn off relay */
				if (Data->cnt >= Data->time)
				{
					Data->cnt = 0;
					Data->Position = RELAY_OFF;
					HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
				}
				else Data->cnt ++;
			}
			break;

		default:;
		}
		break;

	/* Case relay inactive */
	case RELAY_INACTIVE:

		/* Reset counter */
		Data->cnt = 0;

		switch (Data->Mode)
		{
		/* Case positive mode */
		case RELAY_POSITIVE_MODE:
			/* If relay isn't in off position turn off relay */
			if (Data->Position != RELAY_OFF)
			{
				Data->Position = RELAY_OFF;
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
			}
			break;

		/* Case negative mode */
		case RELAY_NEGATIVE_MODE:
			/* If relay isn't in on position turn on relay */
			if (Data->Position != RELAY_ON)
			{
				Data->Position = RELAY_ON;
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
			}
			break;

		default:;
		}
		break;

	default:;
	}
}
