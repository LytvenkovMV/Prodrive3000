
#include "stm32f1xx_hal.h"
#include "setting.h"



#ifndef __relay_h
#define __relay_h

/* Define relay port and pin */
#define RELAY_GPIO_Port		(BO1_GPIO_Port)
#define RELAY_Pin			(BO1_Pin)

/* Relay position */
typedef enum
{
	RELAY_OFF,
	RELAY_ON
} RELAY_Position;

/* Relay state */
typedef enum
{
	RELAY_INACTIVE,
	RELAY_ACTIVE
} RELAY_State;

/* Relay mode */
typedef enum
{
	RELAY_POSITIVE_MODE,
	RELAY_NEGATIVE_MODE
} RELAY_Mode;

/* Signal for relay */
typedef enum
{
	RELAY_NO_SIGNAL,
	RELAY_HEALTH_STATE,
	RELAY_MOTOR_ROTATES,
	RELAY_HIGH_SPEED,
	RELAY_SPEED1,
	RELAY_SPEED2,
	RELAY_MOTOR_FORWARD,
	RELAY_MOTOR_REVERSE,
	RELAY_SAFETY_CONT,
	RELAY_LIMIT_CONT,
	RELAY_MOTOR_TCU,
	RELAY_DRIVE_TEMPERATURE
} RELAY_Signal;

/* Relay data */
typedef struct
{
	RELAY_Signal Signal;
	RELAY_Mode Mode;
	RELAY_State State;
	RELAY_Position Position;
	uint32_t cnt;
	uint32_t time;
} RELAY_Data;

/* Initialize relay */
void RELAY_Init(RELAY_Data *Data, SETTING_Values *SettingValues, uint16_t period_ms);

/* Turn on relay */
void RELAY_TurnOn(RELAY_Position *Position);

/* Turn off relay */
void RELAY_TurnOff(RELAY_Position *Position);

/* Turn on/off relay if necessary */
void RELAY_ChangePosition(RELAY_Data *Data);

#endif /* __relay_h */

/* end of relay.h */
