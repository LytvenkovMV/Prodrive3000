
#include "string.h"
#include "stm32f1xx_hal.h"
#include "bus.h"



#ifndef __INDICATOR_h
#define __INDICATOR_h

/* Dot state */
typedef enum
{
	INDICATOR_DOT_IN_HUNDREDS,
	INDICATOR_DOT_IN_TENS,
	INDICATOR_NO_DOT
} INDICATOR_DotPosition;

/* Indicator data */
typedef struct
{
	uint8_t hundreds;
	uint8_t tens;
	uint8_t ones;
	INDICATOR_DotPosition DotPosition;
} INDICATOR_Data;

/* Print the data on the indicator
 *
 * @input Data structure
 *        .hundreds      ASCII code of the first character
 *        .tens          ASCII code of the second character
 *        .ones          ASCII code of the third character
 *        .DotPosition   Dot position
 */
void INDICATOR_PrintData(INDICATOR_Data Data);

/* Print the text on the indicator
 *
 * @input The text must contain 3 characters, between characters can be one dot. Examples:
 *        "ABC"
 *        "A.b1"
 *        "123"
 *        "1.23"
 *        "12.3"
 *        "0H9"
 *        "EFt"
 * */
void INDICATOR_PrintText(char *text);

#endif /* __INDICATOR_h */

/* end of indicator.h */
