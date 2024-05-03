
#include "display.h"



void DISPLAY_ShowEmptyScreen()
{
	INDICATOR_PrintText("   ");
}



void DISPLAY_ShowInitialScreen(HMI_Status *HMIStatus)
{
	char result[5] = "";
	uint16_t value = 0;

	/* Get speed */
	value = HMIStatus->speed;

	/* Get char value of the speed */
	PRINT_UnsignedDecimal1Place(value, PRINT_RIGHT_ALIGNMENT, result);

	/* Show result on the indicator */
	INDICATOR_PrintText(result);
}



void DISPLAY_ShowMenuScreen(HMI_Status *HMIStatus, SETTING_Values *SettingValues, SENSOR_HMIValues *SensorValues)
{
	MENU_ItemType ItemType;
	SETTING_ArrayID SettingArrayID;
	char line[5];

	ItemType = MENU_GetItemType(HMIStatus->MenuItemID);
	SettingArrayID = MENU_GetSettingArrayID(HMIStatus->MenuItemID);


	switch (HMIStatus->MenuMode)
	{
	case HMI_SELECT:
	{
		MENU_GetLine((HMIStatus->MenuItemID), (HMIStatus->CursorPosition), line);
	}
	break;

	case HMI_WATCH:
	{
		switch (ItemType)
		{
		case MENU_SENSORS_ITEM:	 SENSOR_GetCharValue((HMIStatus->CursorPosition), SensorValues, line); break;
		case MENU_SETTINGS_ITEM: SETTING_GetCharValue(SettingArrayID, (HMIStatus->CursorPosition), SettingValues, line); break;
		default:;
		}
	}
	break;

	case HMI_CHANGE:
	{
		if (ItemType == MENU_SETTINGS_ITEM)
		{
			HMIStatus->beaconCnt++;

			switch(HMIStatus->BeaconState)
			{
			case HMI_BEACON_OFF:
			{
				strcpy(line, "");

				if ((HMIStatus->beaconCnt) >= HMI_BEACON_OFF_TIME)
				{
					HMIStatus->beaconCnt = 0;
					HMIStatus->BeaconState = HMI_BEACON_ON;
				}
			}
			break;

			case HMI_BEACON_ON:
			{
				SETTING_GetCharValue(SettingArrayID, (HMIStatus->CursorPosition), SettingValues, line);

				if ((HMIStatus->beaconCnt) >= HMI_BEACON_ON_TIME)
				{
					HMIStatus->beaconCnt = 0;
					HMIStatus->BeaconState = HMI_BEACON_OFF;
				}
			}
			break;
			}
		}
	}
	break;
	}

	/* Show line on the indicator */
	INDICATOR_PrintText(line);
}



void DISPLAY_ShowMessageScreen(HMI_Status *HMIStatus)
{
	char line[5];
	
	/* Get the message text */
	MESSAGE_GetLine((HMIStatus->MessageID), line);

	/* Show line on the indicator */
	INDICATOR_PrintText(line);
}



void DISPLAY_Update(HMI_Status *HMIStatus, SETTING_Values *SettingValues, SENSOR_HMIValues *SensorValues)
{
	switch(HMIStatus->ScreenType)
	{
	case HMI_INITIAL_SCREEN:
	{
		DISPLAY_ShowInitialScreen(HMIStatus);
	}
	break;
	case HMI_MENU_SCREEN:
	{
		DISPLAY_ShowMenuScreen(HMIStatus, SettingValues, SensorValues);
	}
	break;
	case HMI_MESSAGE_SCREEN:
	{
		DISPLAY_ShowMessageScreen(HMIStatus);
	}
	break;
	default:;
	}
}
