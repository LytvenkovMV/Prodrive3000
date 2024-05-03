
#include "setting.h"
#include "sensor.h"
#include "message.h"
#include "period_config.h"


#ifndef __protection_h
#define __protection_h

/* Protection state */
typedef enum
{
	PROTECTION_RELEASED,
	PROTECTION_TRIPPED
} PROTECTION_State;

/* Thermal state */
typedef enum
{
	PROTECTION_HEATING,
	PROTECTION_COOLING
} PROTECTION_ThermalState;

/* Thermal data */
typedef struct
{
	PROTECTION_ThermalState State;
	float TCU;
	float TCUstart;
	float TCUend;
	float thermalCurrent;
	float thermalCurrentInv;
	float timeToTrip;
	uint32_t coolingTime;
} PROTECTION_ThermalData;

/* Protection counters */
typedef struct
{
	uint32_t cnt1;
	uint32_t cnt2;
	uint32_t cnt3;
} PROTECTION_Counters;

/* Initialize protection */
void PROTECTION_Init(PROTECTION_Counters *Counters, PROTECTION_ThermalData *Data, SETTING_Values *SettingValues);

/* Phase over current protection */
PROTECTION_State PROTECTION_OverCurrent(int16_t value, uint16_t const upperThrd);

/* Protection against the fast phase current rise */
PROTECTION_State PROTECTION_CurrentRise(int16_t currValue, int16_t prevValue, uint16_t const diffThrd);

/* Motor protections */
PROTECTION_State PROTECTION_MotorProt(PROTECTION_Counters *Counters, PROTECTION_ThermalData *ThermalData, MESSAGE_ID *MessageID, SENSOR_Values *SensorValues);

#endif /* __protection_h */

/* end of protection.h */
