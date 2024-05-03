
#include "print.h"



void PRINT_Digit(uint8_t digit, char result[2])
{
	switch (digit)
	{
	case 0: strcpy(result, "0"); break;
	case 1: strcpy(result, "1"); break;
	case 2: strcpy(result, "2"); break;
	case 3: strcpy(result, "3"); break;
	case 4: strcpy(result, "4"); break;
	case 5: strcpy(result, "5"); break;
	case 6: strcpy(result, "6"); break;
	case 7: strcpy(result, "7"); break;
	case 8: strcpy(result, "8"); break;
	case 9: strcpy(result, "9"); break;
	default: strcpy(result, "F");
	}
}



void PRINT_UnsignedInteger(uint16_t value, PRINT_Alignment Alignment, char result[4])
{
	uint8_t digit = 0;
	char temp[2];

	/* Clear result variable */
	strcpy(result, "");

	/* If value bigger than 999 return overflow code */
	if (value > 999)
	{
		strcpy(result, "FFF");
		return;
	}


	/* If value bigger than 99 convert first digit to char */
	if (value > 99)
	{
		digit = value / 100;
		PRINT_Digit(digit, temp);
		strcat(result, temp);
	}
	else
	{
		/* If right alignment add space */
		if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " ");
	}

	/* If value bigger than 9 convert second digit to char */
	if (value > 9)
	{
		digit = (value % 100) / 10;
		PRINT_Digit(digit, temp);
		strcat(result, temp);
	}
	else
	{
		/* If right alignment add space */
		if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " ");
	}

	/* Convert third digit to char */
	digit = value % 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);
}



void PRINT_Integer(int16_t value, PRINT_Alignment Alignment, char result[4])
{
	PRINT_Sign Sign = PRINT_POSITIVE;
	uint8_t digit = 0;
	char temp[2];

	/* Clear result variable */
	strcpy(result, "");

	/* If value bigger than 99 return overflow code */
	if (value > 99)
	{
		if (Alignment == PRINT_RIGHT_ALIGNMENT) strcpy(result, " FF");
		else strcpy(result, "FF");
		return;
	}

	/* If value less than -99 return overflow code */
	if (value < -99)
	{
		strcpy(result, "-FF");
		return;
	}

	/* If value less than 0 */
	if (value < 0)
	{
		Sign = PRINT_NEGATIVE;
		value = - value;
	}

	/* If value bigger than 9 */
	if (value > 9)
	{
		switch (Sign)
		{
		case PRINT_POSITIVE:
		{
			/* If right alignment add space */
			if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " ");
		}
		break;
		case PRINT_NEGATIVE:
		{
			/* Add minus sign */
			strcat(result, "-");
		}
		break;
		}

		/* Convert first digit to char */
		digit = value / 10;
		PRINT_Digit(digit, temp);
		strcat(result, temp);
	}
	else
	{
		switch (Sign)
		{
		case PRINT_POSITIVE:
		{
			/* If right alignment add two spaces */
			if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, "  ");
		}
		break;
		case PRINT_NEGATIVE:
		{
			/* Add minus sign */
			if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " -");
			else strcat(result, "-");
		}
		break;
		}
	}

	/* Convert second digit to char */
	digit = value % 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);
}



void PRINT_UnsignedDecimal1Place(uint16_t value, PRINT_Alignment Alignment, char result[5])
{
	uint8_t digit = 0;
	char temp[2];

	/* Clear result variable */
	strcpy(result, "");

	/* If value bigger than 999 return overflow code */
	if (value > 999)
	{
		strcpy(result, "FF.F");
		return;
	}

	/* If value bigger than 99 convert first digit to char */
	if (value > 99)
	{
		digit = value / 100;
		PRINT_Digit(digit, temp);
		strcat(result, temp);
	}
	else
	{
		/* If right alignment add space */
		if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " ");
	}

	/* Convert second digit to char */
	digit = (value % 100) / 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);

	/* Add dot */
	strcat(result, ".");

	/* Convert third digit to char */
	digit = value % 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);
}



void PRINT_Decimal1Place(int16_t value, PRINT_Alignment Alignment, char result[5])
{
	PRINT_Sign Sign = PRINT_POSITIVE;
	uint8_t digit = 0;
	char temp[2];

	/* Clear result variable */
	strcpy(result, "");

	/* If value bigger than 99 return overflow code */
	if (value > 99)
	{
		if (Alignment == PRINT_RIGHT_ALIGNMENT) strcpy(result, " F.F");
		else strcpy(result, "F.F");
		return;
	}

	/* If value less than -99 return overflow code */
	if (value < -99)
	{
		strcpy(result, "-F.F");
		return;
	}

	/* If value less than 0 */
	if (value < 0)
	{
		Sign = PRINT_NEGATIVE;
		value = - value;
	}

	/* If value bigger than 9 */
	if (value > 9)
	{
		switch (Sign)
		{
		case PRINT_POSITIVE:
		{
			/* If right alignment add space */
			if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " ");
		}
		break;
		case PRINT_NEGATIVE:
		{
			/* Add minus sign */
			strcat(result, "-");
		}
		break;
		}

		/* Convert first digit to char */
		digit = value / 10;
		PRINT_Digit(digit, temp);
		strcat(result, temp);
	}
	else
	{
		switch (Sign)
		{
		case PRINT_POSITIVE:
		{
			/* Add space and zero */
			if (Alignment == PRINT_RIGHT_ALIGNMENT) strcat(result, " 0");
			else strcat(result, "0");
		}
		break;
		case PRINT_NEGATIVE:
		{
			/* Add minus sign and zero */
			strcat(result, "-0");
		}
		break;
		}
	}

	/* Add dot */
	strcat(result, ".");

	/* Convert second digit to char */
	digit = value % 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);
}



void PRINT_UnsignedDecimal2Place(uint16_t value, char result[5])
{
	uint8_t digit = 0;
	char temp[2];

	/* Clear result variable */
	strcpy(result, "");

	/* If value bigger than 999 return overflow code */
	if (value > 999)
	{
		strcpy(result, "F.FF");
		return;
	}

	/* Convert first digit to char */
	digit = value / 100;
	PRINT_Digit(digit, temp);
	strcat(result, temp);

	/* Add dot */
	strcat(result, ".");

	/* Convert second digit to char */
	digit = (value % 100) / 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);

	/* Convert third digit to char */
	digit = value % 10;
	PRINT_Digit(digit, temp);
	strcat(result, temp);
}
