
#include "menu.h"
#include "menu_config.h"



MENU_ItemType MENU_GetItemType(MENU_ItemID ItemID)
{
	if		(ItemID == MENU_ITEM_01) return MENU_CONF_ITEM01_TYPE;
	else if (ItemID == MENU_ITEM_02) return MENU_CONF_ITEM02_TYPE;
	else if (ItemID == MENU_ITEM_03) return MENU_CONF_ITEM03_TYPE;
	else if (ItemID == MENU_ITEM_04) return MENU_CONF_ITEM04_TYPE;
	else if (ItemID == MENU_ITEM_05) return MENU_CONF_ITEM05_TYPE;
	else if (ItemID == MENU_ITEM_06) return MENU_CONF_ITEM06_TYPE;
	else if (ItemID == MENU_ITEM_07) return MENU_CONF_ITEM07_TYPE;
	else if (ItemID == MENU_ITEM_08) return MENU_CONF_ITEM08_TYPE;
	else if (ItemID == MENU_ITEM_09) return MENU_CONF_ITEM09_TYPE;
	else if (ItemID == MENU_ITEM_10) return MENU_CONF_ITEM10_TYPE;
	
	return MENU_CONF_ITEM01_TYPE;
}



uint8_t MENU_GetLastLine(MENU_ItemID ItemID)
{
	if		(ItemID == MENU_ITEM_01) return MENU_CONF_ITEM01_LAST_LINE;
	else if (ItemID == MENU_ITEM_02) return MENU_CONF_ITEM02_LAST_LINE;
	else if (ItemID == MENU_ITEM_03) return MENU_CONF_ITEM03_LAST_LINE;
	else if (ItemID == MENU_ITEM_04) return MENU_CONF_ITEM04_LAST_LINE;
	else if (ItemID == MENU_ITEM_05) return MENU_CONF_ITEM05_LAST_LINE;
	else if (ItemID == MENU_ITEM_06) return MENU_CONF_ITEM06_LAST_LINE;
	else if (ItemID == MENU_ITEM_07) return MENU_CONF_ITEM07_LAST_LINE;
	else if (ItemID == MENU_ITEM_08) return MENU_CONF_ITEM08_LAST_LINE;
	else if (ItemID == MENU_ITEM_09) return MENU_CONF_ITEM09_LAST_LINE;
	else if (ItemID == MENU_ITEM_10) return MENU_CONF_ITEM10_LAST_LINE;
	
	return 2;
}



SETTING_ArrayID MENU_GetSettingArrayID(MENU_ItemID ItemID)
{
	if		(ItemID == MENU_ITEM_01) return MENU_CONF_ITEM01_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_02) return MENU_CONF_ITEM02_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_03) return MENU_CONF_ITEM03_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_04) return MENU_CONF_ITEM04_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_05) return MENU_CONF_ITEM05_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_06) return MENU_CONF_ITEM06_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_07) return MENU_CONF_ITEM07_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_08) return MENU_CONF_ITEM08_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_09) return MENU_CONF_ITEM09_SETTING_ARRAY_ID;
	else if (ItemID == MENU_ITEM_10) return MENU_CONF_ITEM10_SETTING_ARRAY_ID;

	return MENU_CONF_ITEM01_SETTING_ARRAY_ID;
}



void MENU_GetLine(MENU_ItemID ItemID, uint8_t lineNumber, char line[24])
{
	if			(ItemID == MENU_ITEM_01)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM01_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM01_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM01_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM01_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM01_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM01_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM01_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM01_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM01_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM01_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM01_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM01_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM01_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM01_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM01_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM01_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM01_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM01_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM01_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM01_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM01_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM01_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM01_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM01_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM01_LINE25);
	}
	else if	(ItemID == MENU_ITEM_02)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM02_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM02_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM02_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM02_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM02_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM02_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM02_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM02_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM02_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM02_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM02_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM02_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM02_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM02_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM02_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM02_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM02_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM02_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM02_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM02_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM02_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM02_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM02_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM02_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM02_LINE25);
	}
	else if	(ItemID == MENU_ITEM_03)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM03_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM03_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM03_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM03_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM03_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM03_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM03_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM03_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM03_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM03_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM03_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM03_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM03_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM03_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM03_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM03_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM03_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM03_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM03_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM03_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM03_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM03_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM03_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM03_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM03_LINE25);
	}
	else if	(ItemID == MENU_ITEM_04)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM04_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM04_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM04_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM04_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM04_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM04_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM04_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM04_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM04_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM04_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM04_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM04_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM04_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM04_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM04_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM04_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM04_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM04_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM04_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM04_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM04_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM04_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM04_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM04_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM04_LINE25);
	}
	else if	(ItemID == MENU_ITEM_05)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM05_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM05_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM05_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM05_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM05_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM05_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM05_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM05_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM05_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM05_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM05_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM05_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM05_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM05_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM05_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM05_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM05_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM05_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM05_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM05_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM05_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM05_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM05_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM05_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM05_LINE25);
	}	
	else if	(ItemID == MENU_ITEM_06)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM06_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM06_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM06_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM06_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM06_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM06_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM06_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM06_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM06_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM06_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM06_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM06_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM06_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM06_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM06_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM06_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM06_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM06_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM06_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM06_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM06_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM06_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM06_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM06_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM06_LINE25);
	}
	else if	(ItemID == MENU_ITEM_07)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM07_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM07_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM07_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM07_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM07_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM07_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM07_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM07_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM07_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM07_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM07_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM07_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM07_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM07_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM07_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM07_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM07_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM07_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM07_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM07_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM07_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM07_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM07_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM07_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM07_LINE25);
	}
	else if	(ItemID == MENU_ITEM_08)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM08_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM08_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM08_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM08_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM08_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM08_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM08_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM08_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM08_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM08_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM08_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM08_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM08_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM08_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM08_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM08_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM08_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM08_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM08_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM08_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM08_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM08_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM08_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM08_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM08_LINE25);
	}
	else if	(ItemID == MENU_ITEM_09)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM09_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM09_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM09_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM09_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM09_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM09_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM09_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM09_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM09_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM09_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM09_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM09_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM09_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM09_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM09_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM09_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM09_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM09_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM09_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM09_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM09_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM09_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM09_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM09_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM09_LINE25);
	}
	else if	(ItemID == MENU_ITEM_10)
	{
		if		(lineNumber == 1)  strcpy(line, MENU_CONF_ITEM10_LINE01);
		else if	(lineNumber == 2)  strcpy(line, MENU_CONF_ITEM10_LINE02);
		else if	(lineNumber == 3)  strcpy(line, MENU_CONF_ITEM10_LINE03);
		else if	(lineNumber == 4)  strcpy(line, MENU_CONF_ITEM10_LINE04);
		else if	(lineNumber == 5)  strcpy(line, MENU_CONF_ITEM10_LINE05);
		else if	(lineNumber == 6)  strcpy(line, MENU_CONF_ITEM10_LINE06);
		else if	(lineNumber == 7)  strcpy(line, MENU_CONF_ITEM10_LINE07);
		else if	(lineNumber == 8)  strcpy(line, MENU_CONF_ITEM10_LINE08);
		else if	(lineNumber == 9)  strcpy(line, MENU_CONF_ITEM10_LINE09);
		else if	(lineNumber == 10) strcpy(line, MENU_CONF_ITEM10_LINE10);
		else if	(lineNumber == 11) strcpy(line, MENU_CONF_ITEM10_LINE11);
		else if	(lineNumber == 12) strcpy(line, MENU_CONF_ITEM10_LINE12);
		else if	(lineNumber == 13) strcpy(line, MENU_CONF_ITEM10_LINE13);
		else if	(lineNumber == 14) strcpy(line, MENU_CONF_ITEM10_LINE14);
		else if	(lineNumber == 15) strcpy(line, MENU_CONF_ITEM10_LINE15);
		else if	(lineNumber == 16) strcpy(line, MENU_CONF_ITEM10_LINE16);
		else if	(lineNumber == 17) strcpy(line, MENU_CONF_ITEM10_LINE17);
		else if	(lineNumber == 18) strcpy(line, MENU_CONF_ITEM10_LINE18);
		else if	(lineNumber == 19) strcpy(line, MENU_CONF_ITEM10_LINE19);
		else if	(lineNumber == 20) strcpy(line, MENU_CONF_ITEM10_LINE20);
		else if	(lineNumber == 21) strcpy(line, MENU_CONF_ITEM10_LINE21);
		else if	(lineNumber == 22) strcpy(line, MENU_CONF_ITEM10_LINE22);
		else if	(lineNumber == 23) strcpy(line, MENU_CONF_ITEM10_LINE23);
		else if	(lineNumber == 24) strcpy(line, MENU_CONF_ITEM10_LINE24);
		else if	(lineNumber == 25) strcpy(line, MENU_CONF_ITEM10_LINE25);
	}
	else
	{
		strcpy(line, "");
	}
}



MENU_ItemID MENU_GetLink(MENU_ItemID ItemID, uint8_t lineNumber)
{
	if			(ItemID == MENU_ITEM_01)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM01_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM01_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM01_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM01_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM01_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM01_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM01_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM01_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM01_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM01_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM01_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM01_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM01_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM01_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM01_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM01_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM01_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM01_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM01_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM01_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM01_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM01_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM01_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM01_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM01_LINK25;
	}
	else if	(ItemID == MENU_ITEM_02)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM02_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM02_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM02_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM02_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM02_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM02_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM02_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM02_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM02_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM02_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM02_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM02_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM02_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM02_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM02_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM02_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM02_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM02_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM02_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM02_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM02_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM02_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM02_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM02_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM02_LINK25;
	}
	else if	(ItemID == MENU_ITEM_03)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM03_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM03_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM03_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM03_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM03_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM03_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM03_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM03_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM03_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM03_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM03_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM03_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM03_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM03_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM03_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM03_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM03_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM03_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM03_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM03_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM03_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM03_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM03_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM03_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM03_LINK25;
	}
	else if	(ItemID == MENU_ITEM_04)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM04_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM04_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM04_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM04_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM04_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM04_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM04_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM04_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM04_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM04_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM04_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM04_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM04_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM04_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM04_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM04_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM04_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM04_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM04_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM04_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM04_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM04_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM04_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM04_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM04_LINK25;
	}
	else if	(ItemID == MENU_ITEM_05)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM05_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM05_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM05_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM05_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM05_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM05_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM05_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM05_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM05_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM05_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM05_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM05_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM05_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM05_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM05_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM05_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM05_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM05_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM05_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM05_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM05_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM05_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM05_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM05_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM05_LINK25;
	}	
	else if	(ItemID == MENU_ITEM_06)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM06_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM06_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM06_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM06_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM06_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM06_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM06_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM06_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM06_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM06_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM06_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM06_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM06_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM06_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM06_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM06_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM06_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM06_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM06_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM06_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM06_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM06_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM06_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM06_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM06_LINK25;
	}
	else if	(ItemID == MENU_ITEM_07)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM07_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM07_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM07_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM07_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM07_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM07_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM07_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM07_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM07_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM07_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM07_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM07_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM07_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM07_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM07_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM07_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM07_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM07_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM07_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM07_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM07_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM07_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM07_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM07_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM07_LINK25;
	}
	else if	(ItemID == MENU_ITEM_08)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM08_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM08_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM08_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM08_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM08_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM08_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM08_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM08_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM08_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM08_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM08_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM08_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM08_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM08_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM08_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM08_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM08_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM08_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM08_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM08_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM08_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM08_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM08_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM08_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM08_LINK25;
	}
	else if	(ItemID == MENU_ITEM_09)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM09_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM09_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM09_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM09_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM09_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM09_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM09_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM09_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM09_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM09_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM09_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM09_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM09_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM09_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM09_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM09_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM09_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM09_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM09_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM09_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM09_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM09_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM09_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM09_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM09_LINK25;
	}
	else if	(ItemID == MENU_ITEM_10)
	{
		if		(lineNumber == 1)  return MENU_CONF_ITEM10_LINK01;
		else if	(lineNumber == 2)  return MENU_CONF_ITEM10_LINK02;
		else if	(lineNumber == 3)  return MENU_CONF_ITEM10_LINK03;
		else if	(lineNumber == 4)  return MENU_CONF_ITEM10_LINK04;
		else if	(lineNumber == 5)  return MENU_CONF_ITEM10_LINK05;
		else if	(lineNumber == 6)  return MENU_CONF_ITEM10_LINK06;
		else if	(lineNumber == 7)  return MENU_CONF_ITEM10_LINK07;
		else if	(lineNumber == 8)  return MENU_CONF_ITEM10_LINK08;
		else if	(lineNumber == 9)  return MENU_CONF_ITEM10_LINK09;
		else if	(lineNumber == 10) return MENU_CONF_ITEM10_LINK10;
		else if	(lineNumber == 11) return MENU_CONF_ITEM10_LINK11;
		else if	(lineNumber == 12) return MENU_CONF_ITEM10_LINK12;
		else if	(lineNumber == 13) return MENU_CONF_ITEM10_LINK13;
		else if	(lineNumber == 14) return MENU_CONF_ITEM10_LINK14;
		else if	(lineNumber == 15) return MENU_CONF_ITEM10_LINK15;
		else if	(lineNumber == 16) return MENU_CONF_ITEM10_LINK16;
		else if	(lineNumber == 17) return MENU_CONF_ITEM10_LINK17;
		else if	(lineNumber == 18) return MENU_CONF_ITEM10_LINK18;
		else if	(lineNumber == 19) return MENU_CONF_ITEM10_LINK19;
		else if	(lineNumber == 20) return MENU_CONF_ITEM10_LINK20;
		else if	(lineNumber == 21) return MENU_CONF_ITEM10_LINK21;
		else if	(lineNumber == 22) return MENU_CONF_ITEM10_LINK22;
		else if	(lineNumber == 23) return MENU_CONF_ITEM10_LINK23;
		else if	(lineNumber == 24) return MENU_CONF_ITEM10_LINK24;
		else if	(lineNumber == 25) return MENU_CONF_ITEM10_LINK25;
	}
	
	return MENU_CONF_ITEM01_LINK01;
}
