
#include "indicator.h"
#include "hmi.h"
#include "menu.h"
#include "setting.h"
#include "sensor.h"
#include "message.h"

#ifndef __display_h
#define __display_h

/* Show empty screen */
void DISPLAY_ShowEmptyScreen();

/* Update display */
void DISPLAY_Update(HMI_Status *HMIStatus, SETTING_Values *SettingValues, SENSOR_HMIValues *SensorValues);

#endif /* __display_h */

/* end of display.h */
