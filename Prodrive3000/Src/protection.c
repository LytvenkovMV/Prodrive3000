
#include "protection.h"
#include "protection_config.h"



void PROTECTION_Init(PROTECTION_Counters *Counters, PROTECTION_ThermalData *Data, SETTING_Values *SettingValues)
{
	float thermalCurrent = 0, thermalCurrentInv = 0;

	/* Get settings */
	thermalCurrent = ((float)SETTING_GetValue(SETTING_ARRAY_01, 10, SettingValues)) / 100;

	thermalCurrentInv = 1 / thermalCurrent;

	/* Initialize counters */
	Counters->cnt1 = 0;
	Counters->cnt2 = 0;
	Counters->cnt3 = 0;

	/* Initialize thermal data */
	Data->State = PROTECTION_HEATING;
	Data->TCU = 0;
	Data->TCUstart = 0;
	Data->TCUend = 0;
	Data->thermalCurrent = thermalCurrent;
	Data->thermalCurrentInv = thermalCurrentInv;
	Data->timeToTrip = 1;
	Data->coolingTime = 0;
}



PROTECTION_State PROTECTION_OverCurrent(int16_t value, uint16_t const upperThrd)
{
	/* Check the instantaneous current value doesn't exceed the upper threshold */
	if (value < 0) value = - value;
	if (value > upperThrd) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_CurrentRise(int16_t currValue, int16_t prevValue, uint16_t const diffThrd)
{
	int16_t diff = 0;

	/* Check the current rise speed doesn't exceed the limit */
	diff = currValue - prevValue;
	if (diff < 0) diff = - diff;
	if (diff > diffThrd) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_OverHeating(PROTECTION_ThermalData *Data, float currentIL1, float currentIL2, float currentIL3, uint32_t period_ms)
{
	float maxCurrent = 0;
	float thermalCurrentInv = Data->thermalCurrentInv;
	float TCUstart = 0, TCUend = 0;
	float period_s = 0, coolingTime = 0;

	/* Calculate protection period in seconds */
	period_s = ((float)period_ms) / 1000;

	/* Calculate the maximum current */
	maxCurrent = currentIL1;
	if (maxCurrent < currentIL2) maxCurrent = currentIL2;
	if (maxCurrent < currentIL3) maxCurrent = currentIL3;

	/* If maximum current grater than the thermal current it is a heating process */
	if (maxCurrent > (Data->thermalCurrent))
	{
		/* Switch to heating state */
		Data->State = PROTECTION_HEATING;

		/* Calculate time to trip */
		Data->timeToTrip = PROT_CONF_CURVE_MULTIPLIER / ((thermalCurrentInv * thermalCurrentInv * maxCurrent * maxCurrent) - 1);

		/* Calculate thermal capacity used */
		Data->TCU = Data->TCU + 100 * ( period_s / Data->timeToTrip);
	}
	/* Cooling process */
	else
	{
		switch (Data->State)
		{
		case PROTECTION_HEATING:
			/* Save data necessary for calculating the TCU when cooling */
			Data->State = PROTECTION_COOLING;
			Data->coolingTime = 0;
			Data->TCUstart = Data->TCU;
			break;

		case PROTECTION_COOLING:
			Data->coolingTime += period_s;
			break;
		}

		/* Calculate end TCU */
		Data->TCUend = 100 * (Data->thermalCurrentInv) * PROT_CONF_SERVICE_FACTOR_INV * maxCurrent;

		/* Copy variables */
		coolingTime = (float)Data->coolingTime;
		TCUstart = Data->TCUstart;
		TCUend = Data->TCUend;

		/* Calculate TCU */
		Data->TCU = (TCUstart - TCUend) * expf(- coolingTime / PROT_CONF_COOLING_TIME_CONST_S) + TCUend;
	}

	/* If TCU grater than 100% trip protection */
	if ((Data->TCU) > 100) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_BrokenPhase(float currentIL1, float currentIL2, float currentIL3, uint16_t const diffLimit)
{
	float minCurrent = 0, maxCurrent = 0, diff = 0;

	/* Calculate the minimum current */
	minCurrent = currentIL1;
	if (minCurrent > currentIL2) minCurrent = currentIL2;
	if (minCurrent > currentIL3) minCurrent = currentIL3;

	/* Calculate the maximum current */
	maxCurrent = currentIL1;
	if (maxCurrent < currentIL2) maxCurrent = currentIL2;
	if (maxCurrent < currentIL3) maxCurrent = currentIL3;

	/* If the maximum current less than minimum operating value return */
	if (maxCurrent < PROT_CONF_MIN_OPERATING_CURRENT) return PROTECTION_RELEASED;

	/* Calculate the current difference */
	diff = 100 * (maxCurrent - minCurrent) / maxCurrent;

	/* If the difference grater than limit trip protection */
	if (diff >= diffLimit) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_AboveThrd(int16_t value, int16_t const thrd)
{
	/* Check the value doesn't exceed the upper threshold */
	if (value > thrd) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_BelowThrd(int16_t value, int16_t const thrd)
{
	/* Check the value not lower than the lower threshold */
	if (value < thrd) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_Difference(int16_t currValue, int16_t prevValue, uint16_t const thrd)
{
	int16_t diff = 0;

	/* Check the difference doesn't exceed the threshold */
	diff = currValue - prevValue;
	if (diff < 0) diff = - diff;
	if (diff > thrd) return PROTECTION_TRIPPED;

	return PROTECTION_RELEASED;
}



PROTECTION_State PROTECTION_MotorProt(PROTECTION_Counters *Counters, PROTECTION_ThermalData *ThermalData, MESSAGE_ID *MessageID, SENSOR_Values *SensorValues)
{
	PROTECTION_State ProtState = PROTECTION_TRIPPED;

	/* DC over voltage protection */
	ProtState = PROTECTION_AboveThrd(SensorValues->meanVoltageDCint, PROT_CONF_DC_VOLTAGE_UPPER_THRD);
	if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_14; return PROTECTION_TRIPPED;}

	/* DC under voltage protection */
	ProtState = PROTECTION_BelowThrd(SensorValues->meanVoltageDCint, PROT_CONF_DC_VOLTAGE_LOWER_THRD);
	if (ProtState != PROTECTION_RELEASED)







	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////{*MessageID = MESSAGE_13; return PROTECTION_TRIPPED;}













	/* DC voltage differential protection */
	ProtState = PROTECTION_Difference(SensorValues->instVoltageDCBuffer[SENSOR_VOLTAGE_DC_BUFFER_SIZE - 1], SensorValues->instVoltageDCBuffer[SENSOR_VOLTAGE_DC_BUFFER_SIZE - 2], PROT_CONF_DC_DIFFVOLTAGE_THRD);
	if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_11; return PROTECTION_TRIPPED;}



	/* Motor over heating protection */
	/* Execute every 1 second */
	if (Counters->cnt1 <= 0)
	{
		Counters->cnt1 = PERIOD_CONF_MOTOR_OVERHEATING_PROT_MS / PERIOD_CONF_MOTOR_TASK_MS;

		ProtState = PROTECTION_OverHeating(ThermalData, SensorValues->meanCurrentL1, SensorValues->meanCurrentL2, SensorValues->meanCurrentL3, PERIOD_CONF_MOTOR_OVERHEATING_PROT_MS);
		if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_06; return PROTECTION_TRIPPED;}
	}
	else Counters->cnt1 --;



	/* Motor broken phase protection */
	/* Execute every 1 second */
	if (Counters->cnt3 <= 0)
	{
		Counters->cnt3 = PERIOD_CONF_BROKEN_PHASE_PROT_MS / PERIOD_CONF_MOTOR_TASK_MS;

		ProtState = PROTECTION_BrokenPhase(SensorValues->meanCurrentL1, SensorValues->meanCurrentL2, SensorValues->meanCurrentL3, PROT_CONF_CURR_DIFFERENCE_THRD);
		if (ProtState != PROTECTION_RELEASED) Counters->cnt2 ++;
		else Counters->cnt2 = 0;

		/* If the time has elapsed trip protection */
		if (Counters->cnt2 >= PROT_CONF_BROKEN_PHASE_DELAY_S)
		{
			Counters->cnt2 = 0;






			///////////////////////////////////////////////////////////////////////////////////////*MessageID = MESSAGE_05;
			///////////////////////////////////////////////////////////////////////////////////////return PROTECTION_TRIPPED;







		}
	}
	else Counters->cnt3 --;



	/* Inverter over temperature protection */
	ProtState = PROTECTION_AboveThrd(SensorValues->meanTempInverter, PROT_CONF_DRIVE_OVERHEATING_TEMP);
	if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_07; return PROTECTION_TRIPPED;}

	/* Inverter temperature differential protection */
	ProtState = PROTECTION_Difference(SensorValues->instTempInverterBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE - 1], SensorValues->instTempInverterBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE - 2], PROT_CONF_DIFFTEMP_THRD);
	if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_09; return PROTECTION_TRIPPED;}



	/* Rectifier over temperature protection */
	ProtState = PROTECTION_AboveThrd(SensorValues->meanTempRectifier, PROT_CONF_DRIVE_OVERHEATING_TEMP);
	if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_08; return PROTECTION_TRIPPED;}

	/* Rectifier temperature differential protection */
	ProtState = PROTECTION_Difference(SensorValues->instTempRectifierBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE - 1], SensorValues->instTempRectifierBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE - 2], PROT_CONF_DIFFTEMP_THRD);
	if (ProtState != PROTECTION_RELEASED) {*MessageID = MESSAGE_10; return PROTECTION_TRIPPED;}



	return ProtState;
}
