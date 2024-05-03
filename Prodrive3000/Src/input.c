
#include "input.h"



void INPUT_Delay(void)
{
	do
	{
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
	} while (0);
}



void INPUT_Scan(INPUT_States *States)
{
	BUS_Data CurrData;

	States->Input01	= INPUT_RESET;
	States->Input02	= INPUT_RESET;
	States->Input03	= INPUT_RESET;
	States->Input04	= INPUT_RESET;
	States->Input05	= INPUT_RESET;
	States->Input06	= INPUT_RESET;
	States->Input07	= INPUT_RESET;
	States->Input08	= INPUT_RESET;
	States->Input09	= INPUT_RESET;
	States->Input10	= INPUT_RESET;
	States->Input11	= INPUT_RESET;
	States->Input12	= INPUT_RESET;
	States->Input13	= INPUT_RESET;
	States->Input14	= INPUT_RESET;

	/* Bus to input mode */
	BUS_ToInputMode();

	/* Enable output of the register 1 */
	HAL_GPIO_WritePin(OE1_GPIO_Port, OE1_Pin, GPIO_PIN_RESET);
	INPUT_Delay();

	/*********************************** START OF CRITICAL SECTION ***********************************/
	/* Read data from bus */
	taskENTER_CRITICAL();
	BUS_Read(&CurrData);
	taskEXIT_CRITICAL();
	/************************************ END OF CRITICAL SECTION ************************************/

	/* Fill in States variable */
	if (CurrData.D4LineState == BUS_LINE_RESET) States->Input01 = INPUT_SET;
	if (CurrData.D7LineState == BUS_LINE_RESET) States->Input02 = INPUT_SET;
	if (CurrData.D6LineState == BUS_LINE_RESET) States->Input03 = INPUT_SET;
	if (CurrData.D5LineState == BUS_LINE_RESET) States->Input04 = INPUT_SET;
	if (CurrData.D3LineState == BUS_LINE_RESET) States->Input05 = INPUT_SET;
	if (CurrData.D2LineState == BUS_LINE_RESET) States->Input06 = INPUT_SET;
	if (CurrData.D1LineState == BUS_LINE_RESET) States->Input07 = INPUT_SET;
	if (CurrData.D0LineState == BUS_LINE_RESET) States->Input08 = INPUT_SET;

	/* Disable output of the register 1 */
	HAL_GPIO_WritePin(OE1_GPIO_Port, OE1_Pin, GPIO_PIN_SET);
	INPUT_Delay();
	INPUT_Delay();

	/* Enable output of the register 2 */
	HAL_GPIO_WritePin(OE2_GPIO_Port, OE2_Pin, GPIO_PIN_RESET);
	INPUT_Delay();
	
	/*********************************** START OF CRITICAL SECTION ***********************************/
	/* Read data from bus */
	taskENTER_CRITICAL();
	BUS_Read(&CurrData);
	taskEXIT_CRITICAL();
	/************************************ END OF CRITICAL SECTION ************************************/

	/* Fill in States variable */
	if (CurrData.D4LineState == BUS_LINE_RESET) States->Input09 = INPUT_SET;
	if (CurrData.D3LineState == BUS_LINE_RESET) States->Input10 = INPUT_SET;
	if (CurrData.D2LineState == BUS_LINE_RESET) States->Input11 = INPUT_SET;
	if (CurrData.D5LineState == BUS_LINE_RESET) States->Input12 = INPUT_SET;
	if (CurrData.D6LineState == BUS_LINE_RESET) States->Input13 = INPUT_SET;
	if (CurrData.D7LineState == BUS_LINE_RESET) States->Input14 = INPUT_SET;

	/* Disable output of the register 2 */
	HAL_GPIO_WritePin(OE2_GPIO_Port, OE2_Pin, GPIO_PIN_SET);

	INPUT_Delay();
}
