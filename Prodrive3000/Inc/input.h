
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "bus.h"



#ifndef __input_h
#define __input_h

typedef enum
{
	INPUT_RESET,
	INPUT_SET
} INPUT_State;

typedef struct
{
	INPUT_State Input01;
	INPUT_State Input02;
	INPUT_State Input03;
	INPUT_State Input04;
	INPUT_State Input05;
	INPUT_State Input06;
	INPUT_State Input07;
	INPUT_State Input08;
	INPUT_State Input09;
	INPUT_State Input10;
	INPUT_State Input11;
	INPUT_State Input12;
	INPUT_State Input13;
	INPUT_State Input14;
} INPUT_States;

/* Scan inputs */
void INPUT_Scan(INPUT_States *InputStates);

#endif /* __input_h */

/* end of input.h */
