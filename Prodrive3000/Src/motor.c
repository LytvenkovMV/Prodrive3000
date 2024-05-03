
#include "motor.h"



float MOTOR_CalcStep(uint16_t ratedFrequency, uint16_t time, uint16_t taskPeriod)
{
	uint32_t stepsNmb = 0;
	uint32_t time_ms = 0;
	float step = 0;

	/* Calculate time in milliseconds */
	time_ms = time * 1000;

	/* Calculate number of steps */
	stepsNmb = time_ms / taskPeriod;

	/* Calculate step value */
	step = ((float)ratedFrequency) / stepsNmb;

	return step;
}



void MOTOR_Init(MOTOR_State *MotorState, MOTOR_Data *MotorData, MOTOR_Target *MotorTarget, MOTOR_PWMData *PWMData, SETTING_Values *SettingValues)
{
	uint16_t ratedVoltage = 0;
	uint16_t brakeVoltage = 0;
	uint16_t ratedFrequency = 0;
	uint16_t pwmFrequencySelector = 0;
	uint16_t arrRegister = 0, arrRegisterHalf = 0;
	uint16_t brakeTime = 0, freeRunTime = 0;
	uint32_t brakePeriod = 0, freeRunPeriod = 0;
	float accStep = 0, decStep = 0;
	float vfRatio = 0;
	float boostVoltage = 0;
	float pwmPeriod = 0;

	/* Calculate V/f ratio and boost voltage */
	ratedFrequency = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 7, SettingValues);
	ratedVoltage = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 8, SettingValues);

	vfRatio = ((float)ratedVoltage) / ratedFrequency;
	boostVoltage = MOTOR_BOOST_FREQUENCY * vfRatio;

	/* Calculate acceleration and deceleration steps */
	accStep = MOTOR_CalcStep(ratedFrequency, (MotorTarget->accTime), PERIOD_CONF_MOTOR_TASK_MS);
	decStep = MOTOR_CalcStep(ratedFrequency, (MotorTarget->decTime), PERIOD_CONF_MOTOR_TASK_MS);

	/* Get brake voltage */
	brakeVoltage = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 12, SettingValues);

	/* Calculate brake and free run periods */
	brakeTime = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 13, SettingValues);
	freeRunTime = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 14, SettingValues);
	brakePeriod = 100 * brakeTime / PERIOD_CONF_MOTOR_TASK_MS;
	freeRunPeriod = 1000 * freeRunTime / PERIOD_CONF_MOTOR_TASK_MS;

	/* Calculate PWM frequency and period */
	pwmFrequencySelector = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 23, SettingValues);

	switch (pwmFrequencySelector)
	{
	/* Case PWM frequency 2kHz */
	case 0: arrRegister = MOTOR_PWM_TIMER_ARR_REG_2000;
			arrRegisterHalf = MOTOR_PWM_TIMER_ARR_REG_HALF_2000;
			pwmPeriod = 0.0005;
			break;

	/* Case PWM frequency 4kHz */
	case 1: arrRegister = MOTOR_PWM_TIMER_ARR_REG_4000;
			arrRegisterHalf = MOTOR_PWM_TIMER_ARR_REG_HALF_4000;
			pwmPeriod = 0.00025;
			break;

	/* Case PWM frequency 8kHz */
	default: arrRegister = MOTOR_PWM_TIMER_ARR_REG_8000;
			 arrRegisterHalf = MOTOR_PWM_TIMER_ARR_REG_HALF_8000;
			 pwmPeriod = 0.000125;
	}

	/* Initialize motor state */
	MotorState->MessageID = MESSAGE_05;
	MotorState->HealthState = MOTOR_OK;
	MotorState->CurrDirection = MOTOR_FORWARD;
	MotorState->CurrRotation = MOTOR_STOPPED;
	MotorState->StopState = MOTOR_STOP_FINISHED;
	MotorState->ratedVoltage = ratedVoltage;
	MotorState->brakeVoltage = brakeVoltage;
	MotorState->ratedFrequency = ratedFrequency;
	MotorState->arrRegister = arrRegister;
	MotorState->arrRegisterHalf = arrRegisterHalf;
	MotorState->pwmPeriod = pwmPeriod;
	MotorState->boostVoltage = boostVoltage;
	MotorState->vfRatio = vfRatio;
	MotorState->accStep = accStep;
	MotorState->decStep = decStep;
	MotorState->currVoltage = 0;
	MotorState->targetSpeed = 0;
	MotorState->currSpeed = 0;
	MotorState->brakeCnt = 0;
	MotorState->brakePeriod = brakePeriod;
	MotorState->freeRunCnt = 0;
	MotorState->freeRunPeriod = freeRunPeriod;
	MotorState->currentsUpdtCnt = 0;
	MotorState->currentsUpdtPeriod = PERIOD_CONF_CURRENTS_UPDATING_MS / PERIOD_CONF_MOTOR_TASK_MS;
	MotorState->rxTimeoutCnt = 0;
	MotorState->rxErrorsCnt = 0;

	/* Initialize motor data */
	MotorData->HealthState = MOTOR_OK;
	MotorData->MessageID = MESSAGE_01;
	MotorData->MotorRotation = MOTOR_STOPPED;

	/* Initialize PWM data */
	PWMData->Direction = MOTOR_FORWARD;
	PWMData->arrRegisterHalf = 0;
	PWMData->amplitudeMulBy1000 = 0;
	PWMData->angleStep = 0;
}



void MOTOR_InitADCTimer(TIM_HandleTypeDef *htimx)
{
	/* Set ADC sampling rate to 1kHz */
	__HAL_TIM_PRESCALER(htimx, 72);
	__HAL_TIM_SetAutoreload(htimx, 1000);
}



void MOTOR_InitPWMTimer(TIM_HandleTypeDef *htimx, uint16_t const arrReg)
{
	/* Enable timer update interrupt */
	__HAL_TIM_ENABLE_IT(htimx, TIM_IT_UPDATE);

	/* Initialize ARR register */
	__HAL_TIM_SetAutoreload(htimx, arrReg);

	/* Initialize CCR registers */
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_3, 0);
}



uint16_t MOTOR_CalcCurrentUpperThrd(SETTING_Values *SettingValues, float const adcCoeff)
{
	uint16_t result = 0;
	float nomCurrent = 0, cutoffRatio = 0;
	float temp = 0;

	/* Get settings */
	nomCurrent = ((float)SETTING_GetValue(SETTING_ARRAY_01, 9, SettingValues)) / 100;
	cutoffRatio = ((float)SETTING_GetValue(SETTING_ARRAY_01, 11, SettingValues)) / 10;

	temp = 1.414214 * nomCurrent * cutoffRatio / adcCoeff;

	result = (uint16_t)roundf(temp);

	return result;
}



MOTOR_UpdatingStatus MOTOR_UpdateSensorValues(SENSOR_Values *SensorValues, MOTOR_State *MotorState, MESSAGE_ID *MessageID, osMessageQId *CurrentsQueueHandle, osMessageQId *RXDataQueueHandle)
{
	portBASE_TYPE xCurrentsQueueStatus = pdFAIL;
	portBASE_TYPE xRXDataQueueStatus = pdFAIL;
	SENSOR_InstCurrents InstCurrents;
	SENSOR_RXData RXData;
	SENSOR_Status RXDataStatus = SENSOR_FAIL;


	/************************************************** UPDATE CURRENTS ***************************************************/

	/* Receive currents from queue */
	xCurrentsQueueStatus = xQueueReceive(CurrentsQueueHandle, &InstCurrents, 3);

	/* If queue is empty switch to the failure state */
	if (xCurrentsQueueStatus != pdPASS)
	{
		*MessageID = MESSAGE_25;
		return MOTOR_UPDATING_FAIL;
	}
	else
	{
		/* If currents status isn't OK switch to the failure state */
		if (InstCurrents.Status != SENSOR_OK)
		{
			*MessageID = MESSAGE_12;
			return MOTOR_UPDATING_FAIL;
		}
		else
		{
			/* Calculate RMS values */
			SENSOR_CalculateRMSCurrents(&InstCurrents, SensorValues->rmsCurrentBufferL1, SensorValues->rmsCurrentBufferL2, SensorValues->rmsCurrentBufferL3);

			/* If currents updating time has elapsed */
			if (MotorState->currentsUpdtCnt >= MotorState->currentsUpdtPeriod)
			{
				MotorState->currentsUpdtCnt = 0;

				/* Calculate mean values */
				SensorValues->meanCurrentL1 = SENSOR_CalculateMeanCurrent(SensorValues->rmsCurrentBufferL1, SENSOR_RMS_CURR_BUFFER_SIZE);
				SensorValues->meanCurrentL2 = SENSOR_CalculateMeanCurrent(SensorValues->rmsCurrentBufferL2, SENSOR_RMS_CURR_BUFFER_SIZE);
				SensorValues->meanCurrentL3 = SENSOR_CalculateMeanCurrent(SensorValues->rmsCurrentBufferL3, SENSOR_RMS_CURR_BUFFER_SIZE);
			}
			else MotorState->currentsUpdtCnt ++;
		}
	}

	/**********************************************************************************************************************/



	/****************************************** UPDATE DC VOLTAGE AND TEMPERATURES ****************************************/

	/* Receive RXData from queue */
	xRXDataQueueStatus = xQueueReceive(RXDataQueueHandle, &RXData, 0);

	/* If queue is empty */
	if (xRXDataQueueStatus != pdPASS)
	{
		/* If timeout has elapsed switch to the failure state */
		if (MotorState->rxTimeoutCnt >= 10)
		{
			MotorState->rxTimeoutCnt = 0;

			*MessageID = MESSAGE_23;
			return MOTOR_UPDATING_FAIL;
		}
		else MotorState->rxTimeoutCnt ++;
	}
	else
	{
		/* Reset RX timeout counter */
		MotorState->rxTimeoutCnt = 0;

		/* Check RX data for errors */
		RXDataStatus = SENSOR_CheckRXData(&RXData);

		/* If no error */
		if (RXDataStatus == SENSOR_OK)
		{
			MotorState->rxErrorsCnt = 0;

			/* Get sensor values from the RX data */
			SENSOR_HandleRXData(&RXData, SensorValues->instVoltageDCBuffer, SensorValues->instTempRectifierBuffer, SensorValues->instTempInverterBuffer);

			/* Calculate mean values */
			SensorValues->meanVoltageDCfloat = SENSOR_CalculateMeanVoltage(SensorValues->instVoltageDCBuffer, SENSOR_VOLTAGE_DC_BUFFER_SIZE);
			SensorValues->meanVoltageDCint = (uint16_t)roundf(SensorValues->meanVoltageDCfloat);

			SensorValues->meanTempRectifier = SENSOR_CalculateMeanTemperature(SensorValues->instTempRectifierBuffer, SENSOR_TEMPERATURE_BUFFER_SIZE);
			SensorValues->meanTempInverter = SENSOR_CalculateMeanTemperature(SensorValues->instTempInverterBuffer, SENSOR_TEMPERATURE_BUFFER_SIZE);
		}
		else
		{
			/* If errors counter exceeds limit switch to the failure state */
			if (MotorState->rxErrorsCnt >= 10)
			{
				MotorState->rxErrorsCnt = 0;
				*MessageID = MESSAGE_24;
				return MOTOR_UPDATING_FAIL;
			}
			else MotorState->rxErrorsCnt ++;
		}
	}

	/**********************************************************************************************************************/

	return MOTOR_UPDATING_OK;
}



void MOTOR_UpdateData(MOTOR_Data *Data, MOTOR_State *State, SENSOR_Values *SensorValues, float motorTCU)
{
	int16_t currVoltage = 0;
	int16_t currentL1 = 0, currentL2 = 0, currentL3 = 0;
	int16_t tcu = 0;

	Data->HealthState = State->HealthState;
	Data->MessageID = State->MessageID;
	Data->MotorRotation = State->CurrRotation;
	Data->MotorDirection = State->CurrDirection;
	Data->MotorStopState = State->StopState;
	Data->currSpeed = State->currSpeed;

	/* Round values */
	currVoltage = (int16_t)roundf(State->currVoltage);
	currentL1 = (int16_t)roundf(100 * SensorValues->meanCurrentL1);
	currentL2 = (int16_t)roundf(100 * SensorValues->meanCurrentL2);
	currentL3 = (int16_t)roundf(100 * SensorValues->meanCurrentL3);
	tcu = (int16_t)roundf(motorTCU);

	/* Update sensor values for HMI */
	Data->SensorHMIValues.voltageOutput = currVoltage;
	Data->SensorHMIValues.currentL1 = currentL1;
	Data->SensorHMIValues.currentL2 = currentL2;
	Data->SensorHMIValues.currentL3 = currentL3;
	Data->SensorHMIValues.voltageDC = SensorValues->meanVoltageDCint;
	Data->SensorHMIValues.tempRectifier = SensorValues->meanTempRectifier;
	Data->SensorHMIValues.tempInverter = SensorValues->meanTempInverter;
	Data->SensorHMIValues.motorTCU = tcu;
}



MOTOR_SpeedUpdStatus MOTOR_UpdateSpeed(MOTOR_State *State)
{
	/* If current speed and target speed are equal return */
	if ((State->currSpeed) == (State->targetSpeed)) return MOTOR_SPEEDS_EQUAL;

	/* Update current speed */
	/* If current speed grater then target decrease speed */
	if ((State->currSpeed) > (State->targetSpeed))
	{
		State->currSpeed -= State->decStep;
		if ((State->currSpeed) < 0) State->currSpeed = 0;
	}
	/* Else increase speed */
	else if ((State->currSpeed) < (State->targetSpeed))
	{
		State->currSpeed += State->accStep;
		if (State->currSpeed > State->targetSpeed) State->currSpeed = State->targetSpeed;
	}

	/* Update voltage */
	if ((State->currSpeed) <= MOTOR_BOOST_FREQUENCY) State->currVoltage = State->boostVoltage;
	else if ((State->currSpeed) >= (State->ratedFrequency)) State->currVoltage = State->ratedVoltage;
	else State->currVoltage = (State->currSpeed) * (State->vfRatio);

	return MOTOR_SPEEDS_NOT_EQUAL;
}



void MOTOR_StartPWM(TIM_HandleTypeDef *htimx)
{
	/* Reset CCR registers */
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_3, 0);

	/* Start PWM */
	HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(htimx, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(htimx, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(htimx, TIM_CHANNEL_3);
}



void MOTOR_StopPWM(TIM_HandleTypeDef *htimx)
{
	/* Stop PWM */
	HAL_TIMEx_PWMN_Stop(htimx, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(htimx, TIM_CHANNEL_1);

	HAL_TIMEx_PWMN_Stop(htimx, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(htimx, TIM_CHANNEL_2);

	HAL_TIMEx_PWMN_Stop(htimx, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(htimx, TIM_CHANNEL_3);

	/* Reset CCR registers */
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(htimx, TIM_CHANNEL_3, 0);
}



void MOTOR_StartRotation(MOTOR_State *State, double targetSpeed, TIM_HandleTypeDef *htimx)
{
	State->targetSpeed = targetSpeed;
	State->CurrRotation = MOTOR_ROTATES;
	MOTOR_UpdateSpeed(State);
	MOTOR_StartPWM(htimx);
}



void MOTOR_Stop(MOTOR_State *State, TIM_HandleTypeDef *htimx)
{
	MOTOR_SpeedUpdStatus SpeedUpdStatus = MOTOR_SPEEDS_NOT_EQUAL;

	State->targetSpeed = 0;

	switch(State->StopState)
	{
	case MOTOR_BRAKES:

		State->currVoltage = State->brakeVoltage;
		State->brakeCnt ++;

		if (State->brakeCnt >= State->brakePeriod)
		{
			MOTOR_StopPWM(htimx);
			State->brakeCnt = 0;
			State->currSpeed = 0;
			State->currVoltage = 0;
			State->StopState = MOTOR_STOP_FINISHED;
			State->CurrRotation = MOTOR_STOPPED;
		}
		break;

	case MOTOR_FREERUNS:

		MOTOR_StopPWM(htimx);

		State->freeRunCnt ++;
		State->currVoltage = 0;

		if (State->freeRunCnt >= State->freeRunPeriod)
		{
			State->freeRunCnt = 0;
			State->currSpeed = 0;
			State->StopState = MOTOR_STOP_FINISHED;
			State->CurrRotation = MOTOR_STOPPED;
		}
		break;

	case MOTOR_STOPS_SLOW:

		SpeedUpdStatus = MOTOR_UpdateSpeed(State);

		if (SpeedUpdStatus == MOTOR_SPEEDS_EQUAL)
		{
			State->currVoltage = 0;
			State->StopState = MOTOR_STOP_FINISHED;
			State->CurrRotation = MOTOR_STOPPED;
			MOTOR_StopPWM(htimx);
		}
		break;

	default:;
	}
}



void MOTOR_HandleTarget(MOTOR_State *State, MOTOR_Target *Target, TIM_HandleTypeDef *htimx)
{
	MOTOR_Mode TargetMode = Target->Mode;
	float targetSpeed = Target->speed;

	/* Update acceleration and deceleration steps */
	State->accStep = MOTOR_CalcStep(State->ratedFrequency, Target->accTime, PERIOD_CONF_MOTOR_TASK_MS);
	State->decStep = MOTOR_CalcStep(State->ratedFrequency, Target->decTime, PERIOD_CONF_MOTOR_TASK_MS);

	/* Update mode and speed */
	switch(TargetMode)
	{
	case MOTOR_RUN_FORWARD:
		if (State->CurrRotation == MOTOR_STOPPED)
		{
			State->CurrDirection = MOTOR_FORWARD;
			MOTOR_StartRotation(State, targetSpeed, htimx);
		}
		else
		{
			if (State->CurrDirection == MOTOR_FORWARD)
			{
				State->targetSpeed = targetSpeed;
				MOTOR_UpdateSpeed(State);
			}
			else
			{
				State->StopState = MOTOR_STOPS_SLOW;
				MOTOR_Stop(State, htimx);
			}
		}
		break;

	case MOTOR_RUN_REVERSE:
		if (State->CurrRotation == MOTOR_STOPPED)
		{
			State->CurrDirection = MOTOR_REVERSE;
			MOTOR_StartRotation(State, targetSpeed, htimx);
		}
		else
		{
			if (State->CurrDirection == MOTOR_REVERSE)
			{
				State->targetSpeed = targetSpeed;
				MOTOR_UpdateSpeed(State);
			}
			else
			{
				State->StopState = MOTOR_STOPS_SLOW;
				MOTOR_Stop(State, htimx);
			}
		}
		break;

	case MOTOR_STOP_SLOW:
		if (State->CurrRotation != MOTOR_STOPPED)
		{
			State->StopState = MOTOR_STOPS_SLOW;
			MOTOR_Stop(State, htimx);
		}
		break;

	case MOTOR_STOP_FAST:
		if (State->CurrRotation != MOTOR_STOPPED)
		{
			State->StopState = MOTOR_BRAKES;
			MOTOR_Stop(State, htimx);
		}
		break;

	case MOTOR_STOP_FREERUN:
		if (State->CurrRotation != MOTOR_STOPPED)
		{
			State->StopState = MOTOR_FREERUNS;
			MOTOR_Stop(State, htimx);
		}
		break;

	default:;
	}
}



void MOTOR_CalcPWMData(MOTOR_State *State, MOTOR_PWMData *Data, float voltageDC)
{
	float amplitude = 0;

	Data->Direction = State->CurrDirection;
	Data->arrRegisterHalf = State->arrRegisterHalf;

	/* Equations
	 *
	 * A = 2 * Vsm / sqrt(3) / E,
	 * where A - PWM amplitude
	 *       Vsm - output voltage, V
	 *       E - DC bus voltage, V
	 *
	 * S = 2 * PI * f * T,
	 * where S - PWM angle step, radian
	 *       f - output frequency, Hz
	 *       T - PWM period, s
	 *
	 */

	/* Braking */
	if (State->StopState == MOTOR_BRAKES)
	{
		amplitude = 1.154701 * ((float)State->brakeVoltage) / voltageDC;
		Data->amplitudeMulBy1000 = (uint16_t)roundf(1000 * amplitude);
		Data->angleStep = 0;
	}
	/* Normal rotation */
	else
	{
		amplitude = 1.154701 * (State->currVoltage) / voltageDC;
		Data->amplitudeMulBy1000 = (uint16_t)roundf(1000 * amplitude);
		Data->angleStep = 6.283185 * (State->currSpeed) * (State->pwmPeriod);
	}
}













//void MOTOR_CalcCCR(MOTOR_PWMData *PWMData, uint8_t *sectorNumber, float *theta1, uint16_t *ccr1, uint16_t *ccr2, uint16_t *ccr3)
//{
//	float theta2 = 0;
//	float da = 0, db = 0;
//	float temp1 = 0, temp2 = 0, temp3 = 0;
//	uint16_t arrRegisterHalf = 0;
//
//	arrRegisterHalf = (PWMData->arrRegisterHalf);
//
//	/* Modify theta1 angle and sector number */
//	*theta1 += (PWMData->angleStep);
//
//	/* If theta1 angle grater then PI/3 radians */
//	if (*theta1 > 1.047198)
//	{
//		/* Subtract PI/3 from the theta1 angle */
//		*theta1 -= 1.047198;
//
//		/* Modify sector number */
//		*sectorNumber += 1;
//		if (*sectorNumber > 6) *sectorNumber = 1;
//	}
//
//	/* Calculate theta2 angle (PI/3 - theta1) */
//	theta2 = 1.047198 - *theta1;
//
//	/* Calculate da and db values */
//	da = (PWMData->amplitude) * sinf(theta2);
//	db = (PWMData->amplitude) * sinf(*theta1);
//
//	/* Calculate compare register values */
//	switch (*sectorNumber)
//	{
//	case 1:
//		temp1 = arrRegisterHalf * (1 - da - db);
//		temp2 = arrRegisterHalf * (1 + da - db);
//		temp3 = arrRegisterHalf * (1 + da + db);
//	break;
//
//	case 2:
//		temp1 = arrRegisterHalf * (1 - da + db);
//		temp2 = arrRegisterHalf * (1 - da - db);
//		temp3 = arrRegisterHalf * (1 + da + db);
//	break;
//
//	case 3:
//		temp1 = arrRegisterHalf * (1 + da + db);
//		temp2 = arrRegisterHalf * (1 - da - db);
//		temp3 = arrRegisterHalf * (1 + da - db);
//	break;
//
//	case 4:
//		temp1 = arrRegisterHalf * (1 + da + db);
//		temp2 = arrRegisterHalf * (1 - da + db);
//		temp3 = arrRegisterHalf * (1 - da - db);
//	break;
//
//	case 5:
//		temp1 = arrRegisterHalf * (1 + da - db);
//		temp2 = arrRegisterHalf * (1 + da + db);
//		temp3 = arrRegisterHalf * (1 - da - db);
//	break;
//
//	case 6:
//		temp1 = arrRegisterHalf * (1 - da - db);
//		temp2 = arrRegisterHalf * (1 + da + db);
//		temp3 = arrRegisterHalf * (1 - da + db);
//	break;
//
//	default:
//		temp1 = 0;
//		temp2 = 0;
//		temp3 = 0;
//	}
//
//	if (PWMData->Direction == MOTOR_FORWARD)
//	{
//		*ccr1 = (uint16_t)temp1;
//		*ccr2 = (uint16_t)temp2;
//		*ccr3 = (uint16_t)temp3;
//	}
//	else
//	{
//		*ccr1 = (uint16_t)temp3;
//		*ccr2 = (uint16_t)temp2;
//		*ccr3 = (uint16_t)temp1;
//	}
//}












void MOTOR_CalcCCR(MOTOR_PWMData *PWMData, uint8_t *sectorNumber, float *theta1, uint16_t *ccr1, uint16_t *ccr2, uint16_t *ccr3)
{
	float theta2 = 0;
	uint32_t da = 0, db = 0;
	uint32_t temp1 = 0, temp2 = 0, temp3 = 0;
	uint16_t sine1MulBy1000 = 0, sine2MulBy1000 = 0;
	uint16_t arrRegisterHalf = 0;

	arrRegisterHalf = (PWMData->arrRegisterHalf);

	/* Modify theta1 angle and sector number */
	*theta1 += (PWMData->angleStep);

	/* If theta1 angle grater then PI/3 radians */
	if (*theta1 > 1.047198)
	{
		/* Subtract PI/3 from the theta1 angle */
		*theta1 -= 1.047198;

		/* Modify sector number */
		*sectorNumber += 1;
		if (*sectorNumber > 6) *sectorNumber = 1;
	}

	/* Calculate theta2 angle (PI/3 - theta1) */
	theta2 = 1.047198 - *theta1;

	/* Calculate sines multiplied by 1000 */
	sine1MulBy1000 = (uint16_t)roundf(1000 * sinf(*theta1));
	sine2MulBy1000 = (uint16_t)roundf(1000 * sinf(theta2));

	/* Calculate da and db values */
	da = (PWMData->amplitudeMulBy1000) * sine2MulBy1000;
	db = (PWMData->amplitudeMulBy1000) * sine1MulBy1000;

	/* Calculate compare register values */
	switch (*sectorNumber)
	{
	case 1:
		temp1 = arrRegisterHalf * (1000000 - da - db);
		temp2 = arrRegisterHalf * (1000000 + da - db);
		temp3 = arrRegisterHalf * (1000000 + da + db);
	break;

	case 2:
		temp1 = arrRegisterHalf * (1000000 - da + db);
		temp2 = arrRegisterHalf * (1000000 - da - db);
		temp3 = arrRegisterHalf * (1000000 + da + db);
	break;

	case 3:
		temp1 = arrRegisterHalf * (1000000 + da + db);
		temp2 = arrRegisterHalf * (1000000 - da - db);
		temp3 = arrRegisterHalf * (1000000 + da - db);
	break;

	case 4:
		temp1 = arrRegisterHalf * (1000000 + da + db);
		temp2 = arrRegisterHalf * (1000000 - da + db);
		temp3 = arrRegisterHalf * (1000000 - da - db);
	break;

	case 5:
		temp1 = arrRegisterHalf * (1000000 + da - db);
		temp2 = arrRegisterHalf * (1000000 + da + db);
		temp3 = arrRegisterHalf * (1000000 - da - db);
	break;

	case 6:
		temp1 = arrRegisterHalf * (1000000 - da - db);
		temp2 = arrRegisterHalf * (1000000 + da + db);
		temp3 = arrRegisterHalf * (1000000 - da + db);
	break;

	default:
		temp1 = 0;
		temp2 = 0;
		temp3 = 0;
	}

	if (PWMData->Direction == MOTOR_FORWARD)
	{
		*ccr1 = (uint16_t)(temp1 / 1000000);
		*ccr2 = (uint16_t)(temp2 / 1000000);
		*ccr3 = (uint16_t)(temp3 / 1000000);
	}
	else
	{
		*ccr1 = (uint16_t)(temp3 / 1000000);
		*ccr2 = (uint16_t)(temp2 / 1000000);
		*ccr3 = (uint16_t)(temp1 / 1000000);
	}
}

