
#include "message.h"
#include "message_config.h"



void MESSAGE_GetLine(MESSAGE_ID ID, char line[24])
{
	if      (ID == MESSAGE_01) strcpy(line, MESSAGE_CONF_MESS01);
	else if (ID == MESSAGE_02) strcpy(line, MESSAGE_CONF_MESS02);
	else if (ID == MESSAGE_03) strcpy(line, MESSAGE_CONF_MESS03);
	else if (ID == MESSAGE_04) strcpy(line, MESSAGE_CONF_MESS04);
	else if (ID == MESSAGE_05) strcpy(line, MESSAGE_CONF_MESS05);
	else if (ID == MESSAGE_06) strcpy(line, MESSAGE_CONF_MESS06);
	else if (ID == MESSAGE_07) strcpy(line, MESSAGE_CONF_MESS07);
	else if (ID == MESSAGE_08) strcpy(line, MESSAGE_CONF_MESS08);
	else if (ID == MESSAGE_09) strcpy(line, MESSAGE_CONF_MESS09);
	else if (ID == MESSAGE_10) strcpy(line, MESSAGE_CONF_MESS10);
	else if (ID == MESSAGE_11) strcpy(line, MESSAGE_CONF_MESS11);
	else if (ID == MESSAGE_12) strcpy(line, MESSAGE_CONF_MESS12);
	else if (ID == MESSAGE_13) strcpy(line, MESSAGE_CONF_MESS13);
	else if (ID == MESSAGE_14) strcpy(line, MESSAGE_CONF_MESS14);
	else if (ID == MESSAGE_15) strcpy(line, MESSAGE_CONF_MESS15);
	else if (ID == MESSAGE_16) strcpy(line, MESSAGE_CONF_MESS16);
	else if (ID == MESSAGE_17) strcpy(line, MESSAGE_CONF_MESS17);
	else if (ID == MESSAGE_18) strcpy(line, MESSAGE_CONF_MESS18);
	else if (ID == MESSAGE_19) strcpy(line, MESSAGE_CONF_MESS19);
	else if (ID == MESSAGE_20) strcpy(line, MESSAGE_CONF_MESS20);
	else if (ID == MESSAGE_21) strcpy(line, MESSAGE_CONF_MESS21);
	else if (ID == MESSAGE_22) strcpy(line, MESSAGE_CONF_MESS22);
	else if (ID == MESSAGE_23) strcpy(line, MESSAGE_CONF_MESS23);
	else if (ID == MESSAGE_24) strcpy(line, MESSAGE_CONF_MESS24);
	else if (ID == MESSAGE_25) strcpy(line, MESSAGE_CONF_MESS25);
	else if (ID == MESSAGE_26) strcpy(line, MESSAGE_CONF_MESS26);
	else if (ID == MESSAGE_27) strcpy(line, MESSAGE_CONF_MESS27);
	else if (ID == MESSAGE_28) strcpy(line, MESSAGE_CONF_MESS28);
	else if (ID == MESSAGE_29) strcpy(line, MESSAGE_CONF_MESS29);
	else if (ID == MESSAGE_30) strcpy(line, MESSAGE_CONF_MESS30);
	else strcpy(line, "");
}
