
#include "stdint.h"
#include "string.h"
#include "stm32f1xx_hal.h"
#include "print.h"



#ifndef __setting_h
#define __setting_h

/* Verification code that is used to determine whether the settings have been saved or not */
#define SETTING_CODE				((uint32_t) 0xABCD0123)

/* Page address in Flash where the settings will be stored */
#define SETTING_PAGE_ADDRESS		(0x0801FC00)	// Last page address

/* Array addresses */
#define SETTING_ARRAY01_ADDRESS		(SETTING_PAGE_ADDRESS)
#define SETTING_ARRAY02_ADDRESS		(SETTING_PAGE_ADDRESS + 50)
#define SETTING_ARRAY03_ADDRESS		(SETTING_PAGE_ADDRESS + 100)
#define SETTING_ARRAY04_ADDRESS		(SETTING_PAGE_ADDRESS + 150)
#define SETTING_ARRAY05_ADDRESS		(SETTING_PAGE_ADDRESS + 200)

/* Verification code address */
#define SETTING_CODE_ADDRESS		(SETTING_PAGE_ADDRESS + 250)

/*
 * Setting limit type
 *
 * NO_LIMIT			There isn't dynamic limits
 * LOWER_LIMIT		There is only a lower dynamic limit
 * UPPER_LIMIT		There is only an upper dynamic limit
 * FULL_LIMIT		There are lower and upper dynamic limits
 */
typedef enum
{
	SETTING_NO_LIMIT,
	SETTING_LOWER_LIMIT,
	SETTING_UPPER_LIMIT,
	SETTING_FULL_LIMIT
} SETTING_LimitType;

/* 
 * Setting types
 *
 * INTEGER_MINUTE:				Converted to char as the integer value of minutes
 * INTEGER_HOUR:				Converted to char as the integer value of hours
 * INTEGER_DEGREE:				Converted to char as the integer value of degrees
 * 1_DECIMAL_DEGREE:			Converted to char as the value of degrees with one digit after decimal point
 * 2_DECIMAL_DEGREE:			Converted to char as the value of degrees with two digits after decimal point
 * INTEGER_PERCENT:				Converted to char as the integer value of percents
 * 1_DECIMAL_PERCENT:			Converted to char as the value of percents with one digit after decimal point
 * 2_DECIMAL_PERCENT:			Converted to char as the value of percents with two digits after decimal point
 * INTEGER_DEGR_PER_MIN:		Converted to char as the integer value of degrees per a minute
 * 1_DECIMAL_DEGR_PER_MIN:		Converted to char as the value of degrees per a minute with one digit after decimal point
 * 2_DECIMAL_DEGR_PER_MIN:		Converted to char as the value of degrees per a minute with two digits after decimal point
 * INTEGER_UNITLESS:			Converted to char as the integer unitless value
 * 1_DECIMAL_UNITLESS:			Converted to char as the unitless value with one digit after decimal point
 * 2_DECIMAL_UNITLESS:			Converted to char as the unitless value with two digits after decimal point
 */
typedef enum
{
	SETTING_INTEGER_MINUTE,
	SETTING_INTEGER_HOUR,
	SETTING_INTEGER_DEGREE,
	SETTING_1_DECIMAL_DEGREE,
	SETTING_2_DECIMAL_DEGREE,
	SETTING_INTEGER_PERCENT,
	SETTING_1_DECIMAL_PERCENT,
	SETTING_2_DECIMAL_PERCENT,
	SETTING_INTEGER_DEGR_PER_MIN,
	SETTING_1_DECIMAL_DEGR_PER_MIN,
	SETTING_2_DECIMAL_DEGR_PER_MIN,
	SETTING_INTEGER_UNITLESS,
	SETTING_1_DECIMAL_UNITLESS,
	SETTING_2_DECIMAL_UNITLESS,
	SETTING_SELECTOR_TYPE_1,
	SETTING_SELECTOR_TYPE_2,
	SETTING_SELECTOR_TYPE_3,
	SETTING_SELECTOR_TYPE_4,
	SETTING_SELECTOR_TYPE_5,
	SETTING_SELECTOR_TYPE_6,
	SETTING_SELECTOR_TYPE_7,
	SETTING_SELECTOR_TYPE_8
} SETTING_Type;

/* Setting array ID */
typedef enum
{
	SETTING_ARRAY_01,
	SETTING_ARRAY_02,
	SETTING_ARRAY_03,
	SETTING_ARRAY_04,
	SETTING_ARRAY_05
} SETTING_ArrayID;

/* Setting Values structure */
typedef struct
{
	int16_t SETTING_Array01[24];
	int16_t SETTING_Array02[24];
	int16_t SETTING_Array03[24];
	int16_t SETTING_Array04[24];
	int16_t SETTING_Array05[24];
} SETTING_Values;

/* Load settings from FLASH */
void SETTING_Load(SETTING_Values *Values);

/* Save settings in FLASH */
HAL_StatusTypeDef SETTING_Save(SETTING_Values *Values);

/* Get setting value */
int16_t SETTING_GetValue(SETTING_ArrayID ArrayID, uint8_t number, SETTING_Values *Values);

/* Get char representation of the setting value */
void SETTING_GetCharValue(SETTING_ArrayID ArrayID, uint8_t number, SETTING_Values *Values, char result[8]);

/* Decrease setting value */
void SETTING_Decrease(SETTING_ArrayID ArrayID, uint8_t number, SETTING_Values *Values);

/* Increase setting value */
void SETTING_Increase(SETTING_ArrayID ArrayID, uint8_t number, SETTING_Values *Values);

#endif /* __setting_h */

/* end of setting.h */
