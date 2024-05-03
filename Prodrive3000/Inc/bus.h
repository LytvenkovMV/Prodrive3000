
#include "stm32f1xx_hal.h"



#ifndef __bus_h
#define __bus_h

/* Bus line state */
typedef enum
{
	BUS_LINE_RESET = 0U,
	BUS_LINE_SET
} BUS_LineState;



/* Bus data */
typedef struct
{
	BUS_LineState D0LineState;
	BUS_LineState D1LineState;
	BUS_LineState D2LineState;
	BUS_LineState D3LineState;
	BUS_LineState D4LineState;
	BUS_LineState D5LineState;
	BUS_LineState D6LineState;
	BUS_LineState D7LineState;
} BUS_Data;



/* Configure bus to input mode */
void BUS_ToInputMode(void);

/* Read data from the bus */
void BUS_Read(BUS_Data *Data);

/* Configure bus to output mode */
void BUS_ToOutputMode(void);

/* Write data to the bus */
void BUS_Write(BUS_Data Data);

/* Write integer variable to the bus */
void BUS_WriteInteger(uint8_t var);

#endif /* __bus_h */

/* end of bus.h */
