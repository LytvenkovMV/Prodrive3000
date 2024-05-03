
#include "stdint.h"
#include "setting.h"


#ifndef __menu_h
#define __menu_h

/* Item type */
typedef enum
{
	MENU_SUB_ITEM,
	MENU_SENSORS_ITEM,
	MENU_INPUTS_ITEM,
	MENU_OUTPUTS_ITEM,
	MENU_SETTINGS_ITEM,
	MENU_DATE_TIME_ITEM,
	MENU_CONTROL_ITEM,
	MENU_INFO_ITEM
} MENU_ItemType;

/* Item ID */
typedef enum
{
	MENU_ITEM_01,
	MENU_ITEM_02,
	MENU_ITEM_03,
	MENU_ITEM_04,
	MENU_ITEM_05,
	MENU_ITEM_06,
	MENU_ITEM_07,
	MENU_ITEM_08,
	MENU_ITEM_09,
	MENU_ITEM_10
} MENU_ItemID;

/* Get type of the specified item */
MENU_ItemType MENU_GetItemType(MENU_ItemID ItemID);

/* Get last line number of the specified item */
uint8_t MENU_GetLastLine(MENU_ItemID ItemID);

/* Get setting array ID of the specified item */
SETTING_ArrayID MENU_GetSettingArrayID(MENU_ItemID ItemID);

/* Get content of the specified line in the specified item */
void MENU_GetLine(MENU_ItemID ItemID, uint8_t lineNumber, char line[20]);

/* Get link of the specified line in the specified item */
MENU_ItemID MENU_GetLink(MENU_ItemID ItemID, uint8_t lineNumber);

#endif /* __menu_h */

/* end of menu.h */
