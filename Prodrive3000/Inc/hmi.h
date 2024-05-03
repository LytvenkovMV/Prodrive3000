
#include "cmsis_os.h"
#include "button.h"
#include "encoder.h"
#include "menu.h"
#include "setting.h"
#include "message.h"
#include "motor.h"
#include "relay.h"
#include "protection_config.h"
#include "period_config.h"



#ifndef __hmi_h
#define __hmi_h

/* Speed change step */
#define HMI_SPEED_STEP			(1)

/* Beacon ON and OFF times */
#define HMI_BEACON_OFF_TIME		(1)
#define HMI_BEACON_ON_TIME		(3)

/* HMI beacon state */
typedef enum
{
	HMI_BEACON_OFF,
	HMI_BEACON_ON
} HMI_BeaconState;

/* Frequency drive health state */
typedef enum
{
	HMI_DRIVE_FAILURE,
	HMI_DRIVE_OK
} HMI_DriveState;

/* Control location */
typedef enum
{
	HMI_LOCAL_CTRL,
	HMI_REMOTE_CTRL
} HMI_ControlLocation;

/* HMI mode */
typedef enum
{
	HMI_SETUP,
	HMI_WORK
} HMI_SetupMode;

/* HMI menu mode
 *
 * @brief SELECT   select menu line
 *        WATCH    watch current value
 *        CHANGE   change value
 */
typedef enum
{
	HMI_SELECT,
	HMI_WATCH,
	HMI_CHANGE
} HMI_MenuMode;

/* HMI screen type */
typedef enum
{
	HMI_INITIAL_SCREEN,
	HMI_MENU_SCREEN,
	HMI_MESSAGE_SCREEN
} HMI_ScreenType;

/* HMI cursor position */
typedef enum
{
	HMI_CURSOR_IN_LINE1 = 1,
	HMI_CURSOR_IN_LINE2,
	HMI_CURSOR_IN_LINE3,
	HMI_CURSOR_IN_LINE4,
	HMI_CURSOR_IN_LINE5,
	HMI_CURSOR_IN_LINE6,
	HMI_CURSOR_IN_LINE7,
	HMI_CURSOR_IN_LINE8,
	HMI_CURSOR_IN_LINE9,
	HMI_CURSOR_IN_LINE10,
	HMI_CURSOR_IN_LINE11,
	HMI_CURSOR_IN_LINE12,
	HMI_CURSOR_IN_LINE13,
	HMI_CURSOR_IN_LINE14,
	HMI_CURSOR_IN_LINE15,
	HMI_CURSOR_IN_LINE16,
	HMI_CURSOR_IN_LINE17,
	HMI_CURSOR_IN_LINE18,
	HMI_CURSOR_IN_LINE19,
	HMI_CURSOR_IN_LINE20,
	HMI_CURSOR_IN_LINE21,
	HMI_CURSOR_IN_LINE22,
	HMI_CURSOR_IN_LINE23,
	HMI_CURSOR_IN_LINE24,
	HMI_CURSOR_IN_LINE25
} HMI_CursorPosition;

/* HMI update */
typedef enum
{
	HMI_UPDATE_NOT_REQUIRED,
	HMI_UPDATE_REQUIRED
} HMI_Update;

/* HMI setting status */
typedef enum
{
	HMI_SETTING_UP_TO_DATE,
	HMI_SETTING_CHANGED
} HMI_SettingStatus;

/* HMI status */
typedef struct
{
	HMI_DriveState DriveState;
	HMI_SettingStatus SettingStatus;
	HMI_ControlLocation ControlLocation;
	HMI_SetupMode SetupMode;
	HMI_MenuMode MenuMode;
	HMI_ScreenType ScreenType;
	HMI_CursorPosition CursorPosition;
	HMI_BeaconState BeaconState;
	uint32_t beaconCnt;
	HMI_Update DisplayUpdate;
	HMI_Update MotorUpdate;
	MENU_ItemID MenuItemID;
	MESSAGE_ID MessageID;
	uint16_t speed;
	uint32_t motorDataCnt;
	uint32_t displayCnt;
	uint32_t motorDataPeriod;
	uint32_t displayPeriod;
} HMI_Status;

/* Initialize HMI */
void HMI_Init(HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget);

/* Switch to drive failure state */
void HMI_SwitchToFailure(HMI_Status *HMIStatus, MESSAGE_ID MessageID);

/* Handle buttons */
void HMI_HandleButtons(BUTTON_Command Command, HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Target *MotorTarget);

/* Handle encoder */
void HMI_HandleEncoder(ENCODER_Command Command, HMI_Status *HMIStatus, SETTING_Values *SettingValues, MOTOR_Data MotorData, MOTOR_Target *MotorTarget);

/* Handle relay */
void HMI_HandleRelay(HMI_Status *Status, MOTOR_Data *MotorData, BUTTON_SafetyState SafetyState, BUTTON_LimitState FwdLimitState, BUTTON_LimitState RevLimitState, RELAY_Data *RelayData, SETTING_Values *SettingValues);

#endif /* __hmi_h */

/* end of hmi.h */
