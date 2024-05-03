
#include "bus.h"


void BUS_ToInputMode(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*All bus pins to input mode*/
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	/*Configure GPIO pin : D0_Pin */
	GPIO_InitStruct.Pin = D0_Pin;
	HAL_GPIO_Init(D0_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : D1_Pin */
	GPIO_InitStruct.Pin = D1_Pin;
	HAL_GPIO_Init(D1_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D2_Pin */
	GPIO_InitStruct.Pin = D2_Pin;
	HAL_GPIO_Init(D2_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D3_Pin */
	GPIO_InitStruct.Pin = D3_Pin;
	HAL_GPIO_Init(D3_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D4_Pin */
	GPIO_InitStruct.Pin = D4_Pin;
	HAL_GPIO_Init(D4_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D5_Pin */
	GPIO_InitStruct.Pin = D5_Pin;
	HAL_GPIO_Init(D5_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D6_Pin */
	GPIO_InitStruct.Pin = D6_Pin;
	HAL_GPIO_Init(D6_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D7_Pin */
	GPIO_InitStruct.Pin = D7_Pin;
	HAL_GPIO_Init(D7_GPIO_Port, &GPIO_InitStruct);
}	



void BUS_Read(BUS_Data *Data)
{
	GPIO_PinState pinState = GPIO_PIN_RESET;

	pinState = HAL_GPIO_ReadPin(D0_GPIO_Port, D0_Pin);
	if (pinState == GPIO_PIN_SET) Data->D0LineState = BUS_LINE_SET; else Data->D0LineState = BUS_LINE_RESET;
	
	pinState = HAL_GPIO_ReadPin(D1_GPIO_Port, D1_Pin);
	if (pinState == GPIO_PIN_SET) Data->D1LineState = BUS_LINE_SET; else Data->D1LineState = BUS_LINE_RESET;
	
	pinState = HAL_GPIO_ReadPin(D2_GPIO_Port, D2_Pin);
	if (pinState == GPIO_PIN_SET) Data->D2LineState = BUS_LINE_SET; else Data->D2LineState = BUS_LINE_RESET;

	pinState = HAL_GPIO_ReadPin(D3_GPIO_Port, D3_Pin);
	if (pinState == GPIO_PIN_SET) Data->D3LineState = BUS_LINE_SET; else Data->D3LineState = BUS_LINE_RESET;

	pinState = HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin);
	if (pinState == GPIO_PIN_SET) Data->D4LineState = BUS_LINE_SET; else Data->D4LineState = BUS_LINE_RESET;

	pinState = HAL_GPIO_ReadPin(D5_GPIO_Port, D5_Pin);
	if (pinState == GPIO_PIN_SET) Data->D5LineState = BUS_LINE_SET; else Data->D5LineState = BUS_LINE_RESET;

	pinState = HAL_GPIO_ReadPin(D6_GPIO_Port, D6_Pin);
	if (pinState == GPIO_PIN_SET) Data->D6LineState = BUS_LINE_SET; else Data->D6LineState = BUS_LINE_RESET;

	pinState = HAL_GPIO_ReadPin(D7_GPIO_Port, D7_Pin);
	if (pinState == GPIO_PIN_SET) Data->D7LineState = BUS_LINE_SET; else Data->D7LineState = BUS_LINE_RESET;
}



void BUS_ToOutputMode(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
		
	/*All bus pins to output mode*/
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	/*Configure GPIO pin : D0_Pin */
	GPIO_InitStruct.Pin = D0_Pin;
	HAL_GPIO_Init(D0_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : D1_Pin */
	GPIO_InitStruct.Pin = D1_Pin;
	HAL_GPIO_Init(D1_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D2_Pin */
	GPIO_InitStruct.Pin = D2_Pin;
	HAL_GPIO_Init(D2_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D3_Pin */
	GPIO_InitStruct.Pin = D3_Pin;
	HAL_GPIO_Init(D3_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D4_Pin */
	GPIO_InitStruct.Pin = D4_Pin;
	HAL_GPIO_Init(D4_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D5_Pin */
	GPIO_InitStruct.Pin = D5_Pin;
	HAL_GPIO_Init(D5_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D6_Pin */
	GPIO_InitStruct.Pin = D6_Pin;
	HAL_GPIO_Init(D6_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : D7_Pin */
	GPIO_InitStruct.Pin = D7_Pin;
	HAL_GPIO_Init(D7_GPIO_Port, &GPIO_InitStruct);
}



void BUS_Write(BUS_Data Data)
{
	if (Data.D0LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_RESET);
	if (Data.D1LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
	if (Data.D2LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
	if (Data.D3LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_RESET);
	if (Data.D4LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);
	if (Data.D5LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
	if (Data.D6LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
	if (Data.D7LineState == BUS_LINE_SET) HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
}



void BUS_WriteInteger(uint8_t data)
{
	if (data & 0x01) HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_RESET);
	if (data & 0x02) HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
	if (data & 0x04) HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
	if (data & 0x08) HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_RESET);
	if (data & 0x10) HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);
	if (data & 0x20) HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
	if (data & 0x40) HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
	if (data & 0x80) HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
}
