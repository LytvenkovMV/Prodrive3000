
#include "input.h"
#include "setting.h"



#ifndef __button_h
#define __button_h

/* Delay before the fast change first command */
#define BUTTON_DELAY_BEFORE_FAST_CHG		(150)

/* Delay between the fast change commands */
#define BUTTON_DELAY_BETWEEN_FAST_CHG		(10)

/* Button state */
typedef enum
{
	BUTTON_RELEASED,
	BUTTON_PUSHED
} BUTTON_State;

/* Button safety contact state */
typedef enum
{
	BUTTON_SAFETY_TRIPPED,
	BUTTON_SAFETY_RELEASED
} BUTTON_SafetyState;

/* Button limit contact state */
typedef enum
{
	BUTTON_LIMIT_TRIPPED,
	BUTTON_LIMIT_RELEASED
} BUTTON_LimitState;

/* Mechanism movement direction */
typedef enum
{
	BUTTON_FORWARD,
	BUTTON_REVERSE
} BUTTON_Direction;

/* Button states */
typedef struct
{
	BUTTON_State CurrLocalSlowStop;
	BUTTON_State CurrLocalFwd;
	BUTTON_State CurrLocalRev;
	BUTTON_State CurrLocalFastStop;
	BUTTON_State CurrRemoteSlowStop;
	BUTTON_State CurrRemoteFwd;
	BUTTON_State CurrRemoteRev;
	BUTTON_State CurrRemoteCustom1;
	BUTTON_State CurrRemoteCustom2;
	BUTTON_State CurrRemoteCustom3;
	BUTTON_State PrevLocalSlowStop;
	BUTTON_State PrevLocalFwd;
	BUTTON_State PrevLocalRev;
	BUTTON_State PrevLocalFastStop;
	BUTTON_State PrevRemoteSlowStop;
	BUTTON_State PrevRemoteFwd;
	BUTTON_State PrevRemoteRev;
	BUTTON_State PrevRemoteCustom1;
	BUTTON_State PrevRemoteCustom2;
	BUTTON_State PrevRemoteCustom3;
} BUTTON_States;

/* Button counters */
typedef struct
{
	uint16_t custom1cnt1;
	uint16_t custom1cnt2;
	uint16_t custom2cnt1;
	uint16_t custom2cnt2;
	uint16_t custom3cnt1;
	uint16_t custom3cnt2;
} BUTTON_Counters;

/* Control location */
typedef enum
{
	BUTTON_LOCAL_CONTROL,
	BUTTON_REMOTE_CONTROL
} BUTTON_ControlLocation;

/* Control scheme */
typedef enum
{
	BUTTON_3_WIRE_CONTROL,
	BUTTON_2_WIRE_CONTROL
} BUTTON_ControlScheme;

/* Run permission */
typedef enum
{
	BUTTON_RUN_NOT_ALLOWED,
	BUTTON_RUN_ALLOWED
} BUTTON_RunPermission;

/* Custom button function */
typedef enum
{
	BUTTON_NO_FUNC,
	BUTTON_FUNC_DECREASE_SPEED,
	BUTTON_FUNC_INCREASE_SPEED,
	BUTTON_FUNC_SPEED1,
	BUTTON_FUNC_SPEED2,
	BUTTON_FUNC_STOP_FAST,
	BUTTON_FUNC_STOP_FREERUN,
	BUTTON_FUNC_SAFETY_NO,
	BUTTON_FUNC_SAFETY_NC,
	BUTTON_FUNC_LIMIT_FWD_NO,
	BUTTON_FUNC_LIMIT_FWD_NC,
	BUTTON_FUNC_LIMIT_REV_NO,
	BUTTON_FUNC_LIMIT_REV_NC
} BUTTON_Function;

/* Button settings */
typedef struct
{
	BUTTON_ControlLocation ControlLocation;
	BUTTON_ControlScheme ControlScheme;
	BUTTON_Function Function1;
	BUTTON_Function Function2;
	BUTTON_Function Function3;
} BUTTON_Settings;

/* Button status */
typedef enum
{
	BUTTON_NOT_CHANGED,
	BUTTON_CHANGED
} BUTTON_Status;

/* Button command */
typedef enum
{
	BUTTON_CMD_STOP_FAST,
	BUTTON_CMD_STOP_SLOW,
	BUTTON_CMD_STOP_FREERUN,
	BUTTON_CMD_RUN_FORWARD,
	BUTTON_CMD_RUN_REVERSE,
	BUTTON_CMD_DECREASE_SPEED,
	BUTTON_CMD_INCREASE_SPEED,
	BUTTON_CMD_SET_SPEED1,
	BUTTON_CMD_SET_SPEED2,
} BUTTON_Command;

/* Initialize buttons */
void BUTTON_Init(BUTTON_States *ButtonStates, BUTTON_Counters *ButtonCounters, BUTTON_Settings *ButtonSettings, INPUT_States *InputStates, SETTING_Values *SettingValues);

/* Update button states */
void BUTTON_UpdateStates(BUTTON_States *ButtonStates, INPUT_States *InputStates);

/* Get safety contact state */
BUTTON_SafetyState BUTTON_GetSafetyState(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings);

/* Get forward limit switch state */
BUTTON_LimitState BUTTON_GetFwdLimitState(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings);

/* Get reverse limit switch state */
BUTTON_LimitState BUTTON_GetRevLimitState(BUTTON_States *ButtonStates, BUTTON_Settings *ButtonSettings);

/* Analyze current and previous button states and assign the command from button */
BUTTON_Status BUTTON_GetCommand(BUTTON_Command *Command, BUTTON_States *ButtonStates, BUTTON_Counters *Counters, BUTTON_Direction Direction, BUTTON_Settings *ButtonSettings);

#endif /* __button_h */

/* end of button.h */
