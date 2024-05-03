
#include <indicator.h>



void INDICATOR_Delay5(void)
{
	do
	{
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
	} while (0);
}



uint8_t INDICATOR_ConvertASCIItoSS(uint8_t asciiCode)
{
	switch (asciiCode)
	{
	case 32:  return 0b11111111;		// [SPACE]
	case 45:  return 0b11011111;		// -
	case 48:  return 0b10100000;		// 0
	case 49:  return 0b10101111;		// 1
	case 50:  return 0b11000100;		// 2
	case 51:  return 0b10000110;		// 3
	case 52:  return 0b10001011;		// 4
	case 53:  return 0b10010010;		// 5
	case 54:  return 0b10010000;		// 6
	case 55:  return 0b10100111;		// 7
	case 56:  return 0b10000000;		// 8
	case 57:  return 0b10000010;		// 9
	case 65:  return 0b10000001;		// A
	case 66:  return 0b10000000;		// B
	case 67:  return 0b11110000;		// C
	case 68:  return 0b10100000;		// D
	case 69:  return 0b11010000;		// E
	case 70:  return 0b11010001;		// F
	case 71:  return 0b10110000;		// G
	case 72:  return 0b10001001;		// H
	case 73:  return 0b11111001;		// I
	case 74:  return 0b10101100;		// J
	case 76:  return 0b11111000;		// L
	case 78:  return 0b10100001;		// N
	case 79:  return 0b10100000;		// O
	case 80:  return 0b11000001;		// P
	case 83:  return 0b10010010;		// S
	case 85:  return 0b10101000;		// U
	case 88:  return 0b10001001;		// X
	case 89:  return 0b10001010;		// Y
	case 90:  return 0b11000100;		// Z
	case 95:  return 0b11111110;		// _
	case 97:  return 0b10000100;		// a
	case 98:  return 0b10011000;		// b
	case 99:  return 0b11011100;		// c
	case 100: return 0b10001100;		// d
	case 104: return 0b10011001;		// h
	case 105: return 0b11111101;		// i
	case 108: return 0b11111001;		// l
	case 110: return 0b10011101;		// n
	case 111: return 0b10011100;		// o
	case 114: return 0b11011101;		// r
	case 116: return 0b11011000;		// t
	case 117: return 0b10111100;		// u
	}

	return 0xFF;
}



void INDICATOR_PrintData(INDICATOR_Data Data)
{
	uint8_t hundreds, tens, ones;

	/* Wait for previous operation to complete */
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	
	/*************Calculate seven segment codes ************/
	/* Convert ASCII codes to seven segment codes */
	hundreds = INDICATOR_ConvertASCIItoSS(Data.hundreds);
	tens     = INDICATOR_ConvertASCIItoSS(Data.tens);
	ones     = INDICATOR_ConvertASCIItoSS(Data.ones);

	/* Add dot if necessary */
	switch (Data.DotPosition)
	{
	case INDICATOR_DOT_IN_HUNDREDS: hundreds = hundreds & 0b01111111; break;
	case INDICATOR_DOT_IN_TENS:     tens = tens & 0b01111111;         break;
	default:;
	}

	/* Switch bus to output mode */
	BUS_ToOutputMode();

	/****************** Print hundreds ********************/
	/* Write code to the bus */
	BUS_WriteInteger(hundreds);
	INDICATOR_Delay5();

	/* Latch code in the register */
	HAL_GPIO_WritePin(LE2_GPIO_Port, LE2_Pin, GPIO_PIN_SET);
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	HAL_GPIO_WritePin(LE2_GPIO_Port, LE2_Pin, GPIO_PIN_RESET);
	
	/******************** Print tens **********************/
	/* Write code to the bus */
	BUS_WriteInteger(tens);
	INDICATOR_Delay5();

	/* Latch code in the register */
	HAL_GPIO_WritePin(LE1_GPIO_Port, LE1_Pin, GPIO_PIN_SET);
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	HAL_GPIO_WritePin(LE1_GPIO_Port, LE1_Pin, GPIO_PIN_RESET);

	/******************** Print ones **********************/
	/* Write code to the bus */
	BUS_WriteInteger(ones);
	INDICATOR_Delay5();

	/* Latch code in the register */
	HAL_GPIO_WritePin(LE0_GPIO_Port, LE0_Pin, GPIO_PIN_SET);
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	INDICATOR_Delay5();
	HAL_GPIO_WritePin(LE0_GPIO_Port, LE0_Pin, GPIO_PIN_RESET);

	/* Return bus to input mode */
	BUS_ToInputMode();
}



void INDICATOR_PrintText(char text[5])
{
	INDICATOR_Data Data;
	uint8_t temp = 0, length = 0;
	char string[5] = "";

	/* Specify initial dot position */
	Data.DotPosition = INDICATOR_NO_DOT;

	/* Copy text */
	strcpy(string, text);

	/* If length of text less than 4 characters add spaces */
	length = strlen(string);
	if (length == 0) strcat(string, "    ");
	if (length == 1) strcat(string, "   ");
	if (length == 2) strcat(string, "  ");
	if (length == 3) strcat(string, " ");

	/* Get first character from text */
	temp = string[0];

	/* Copy character */
	Data.hundreds = temp;

	/* Get second character from text */
	temp = string[1];

	/* If second character is "." or "," */
	if ((temp == 44) || (temp == 46))
	{
		/* Specify dot position */
		Data.DotPosition = INDICATOR_DOT_IN_HUNDREDS;

		/* Get third character from the text */
		temp = string[2];

		/* Copy third character */
		Data.tens = temp;

		/* Get fourth character */
		temp = string[3];

		/* Copy fourth character */
		Data.ones = temp;
	}
	else
	{
		/* Copy second character */
		Data.tens = temp;

		/* Get third character */
		temp = string[2];

		/* If third character is "." or "," */
		if ((temp == 44) || (temp == 46))
		{
			/* Specify dot position */
			Data.DotPosition = INDICATOR_DOT_IN_TENS;

			/* Get fourth character */
			temp = string[3];

			/* Copy fourth character */
			Data.ones = temp;
		}
		else
		{
			/* Copy third character */
			Data.ones = temp;
		}
	}

	/* Print data */
	INDICATOR_PrintData(Data);
}
