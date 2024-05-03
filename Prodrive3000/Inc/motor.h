
#include "stm32f1xx_hal.h"
#include "stm32_hal_legacy.h"
#include "sensor.h"
#include "message.h"
#include "setting.h"
#include "period_config.h"



#ifndef __motor_h
#define __motor_h

/* Motor boost frequency in Hz */
#define MOTOR_BOOST_FREQUENCY				(5)

/* PWM timer ARR register values */
/* PWM frequency 2000Hz */
#define MOTOR_PWM_TIMER_ARR_REG_2000		(18000)

/* PWM frequency 4000Hz */
#define MOTOR_PWM_TIMER_ARR_REG_4000		(9000)

/* PWM frequency 8000Hz */
#define MOTOR_PWM_TIMER_ARR_REG_8000		(4500)

/* PWM timer ARR register values divided by 2 */
/* PWM frequency 2000Hz */
#define MOTOR_PWM_TIMER_ARR_REG_HALF_2000	(9000)

/* PWM frequency 4000Hz */
#define MOTOR_PWM_TIMER_ARR_REG_HALF_4000	(4500)

/* PWM frequency 8000Hz */
#define MOTOR_PWM_TIMER_ARR_REG_HALF_8000	(2250)

/* Motor updating status */
typedef enum
{
	MOTOR_UPDATING_FAIL,
	MOTOR_UPDATING_OK
} MOTOR_UpdatingStatus;

/* Motor health state */
typedef enum
{
	MOTOR_FAILURE,
	MOTOR_OK
} MOTOR_HealthState;

/* Motor rotation */
typedef enum
{
	MOTOR_ROTATES,
	MOTOR_STOPPED
} MOTOR_Rotation;

/* Motor direction of the rotation */
typedef enum
{
	MOTOR_FORWARD,
	MOTOR_REVERSE
} MOTOR_Direction;

/* Motor stop state */
typedef enum
{
	MOTOR_STOPS_SLOW,
	MOTOR_BRAKES,
	MOTOR_FREERUNS,
	MOTOR_STOP_FINISHED
} MOTOR_StopState;

/* Motor speed updating status */
typedef enum
{
	MOTOR_SPEEDS_NOT_EQUAL,
	MOTOR_SPEEDS_EQUAL
} MOTOR_SpeedUpdStatus;

/* Motor data */
typedef struct
{
	MOTOR_HealthState HealthState;
	MOTOR_Rotation MotorRotation;
	MOTOR_Direction MotorDirection;
	MOTOR_StopState MotorStopState;
	float currSpeed;
	SENSOR_HMIValues SensorHMIValues;
	MESSAGE_ID MessageID;
} MOTOR_Data;

/* Motor mode */
typedef enum
{
	MOTOR_STOP_SLOW,
	MOTOR_STOP_FAST,
	MOTOR_STOP_FREERUN,
	MOTOR_RUN_FORWARD,
	MOTOR_RUN_REVERSE
} MOTOR_Mode;

/* Motor target */
typedef struct
{
	MOTOR_Mode Mode;
	float speed;
	uint16_t accTime;
	uint16_t decTime;
} MOTOR_Target;

/* Motor overall state */
typedef struct
{
	MESSAGE_ID MessageID;
	MOTOR_HealthState HealthState;
	MOTOR_Rotation CurrRotation;
	MOTOR_Direction CurrDirection;
	MOTOR_StopState StopState;
	uint16_t ratedVoltage;
	uint16_t brakeVoltage;
	uint16_t ratedFrequency;
	uint16_t arrRegister;
	uint16_t arrRegisterHalf;
	float pwmPeriod;
	float boostVoltage;
	float vfRatio;
	float accStep;
	float decStep;
	float currVoltage;
	float targetSpeed;
	float currSpeed;
	uint32_t brakeCnt;
	uint32_t brakePeriod;
	uint32_t freeRunCnt;
	uint32_t freeRunPeriod;
	uint32_t currentsUpdtCnt;
	uint32_t currentsUpdtPeriod;
	uint32_t rxTimeoutCnt;
	uint32_t rxErrorsCnt;
} MOTOR_State;

/* Motor PWM data */
typedef struct
{
	MOTOR_Direction Direction;
	uint16_t arrRegisterHalf;
	uint16_t amplitudeMulBy1000;
	float angleStep;
} MOTOR_PWMData;

/* Initialize motor variables */
void MOTOR_Init(MOTOR_State *MotorState, MOTOR_Data *MotorData, MOTOR_Target *MotorTarget, MOTOR_PWMData *PWMData, SETTING_Values *SettingValues);

/* Initialize timer used to drive the ADC */
void MOTOR_InitADCTimer(TIM_HandleTypeDef *htimx);

/* Initialize timer used for PWM */
void MOTOR_InitPWMTimer(TIM_HandleTypeDef *htimx, uint16_t const arrReg);

/* Calculate instantaneous current upper threshold */
uint16_t MOTOR_CalcCurrentUpperThrd(SETTING_Values *SettingValues, float const adcCoeff);

/* Update sensor values */
MOTOR_UpdatingStatus MOTOR_UpdateSensorValues(SENSOR_Values *SensorValues, MOTOR_State *MotorState, MESSAGE_ID *MessageID, osMessageQId *CurrentsQueueHandle, osMessageQId *RXDataQueueHandle);

/* Update motor data */
void MOTOR_UpdateData(MOTOR_Data *Data, MOTOR_State *State, SENSOR_Values *SensorValues, float motorTCU);

/* Start PWM */
void MOTOR_StartPWM(TIM_HandleTypeDef *htimx);

/* Stop PWM */
void MOTOR_StopPWM(TIM_HandleTypeDef *htimx);

/* Handle motor target */
void MOTOR_HandleTarget(MOTOR_State *State, MOTOR_Target *Target, TIM_HandleTypeDef *htimx);

/* Calculate PWM data */
void MOTOR_CalcPWMData(MOTOR_State *State, MOTOR_PWMData *Data, float voltageDC);

/* Calculate compare register values */
void MOTOR_CalcCCR(MOTOR_PWMData *PWMData, uint8_t *sectorNumber, float *theta1, uint16_t *ccr1, uint16_t *ccr2, uint16_t *ccr3);

#endif /* __motor_h */

/* end of motor.h */
