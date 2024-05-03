
#include "stdio.h"
#include "string.h"



#ifndef __print_h
#define __print_h

/* Value sign */
typedef enum
{
	PRINT_POSITIVE,
	PRINT_NEGATIVE
} PRINT_Sign;

/* Print alignment */
typedef enum
{
	PRINT_LEFT_ALIGNMENT,
	PRINT_RIGHT_ALIGNMENT
} PRINT_Alignment;

/* Print unsigned integer
 *
 * @ value must be less then   1000
 * @ value must be bigger then 0
 */
void PRINT_UnsignedInteger(uint16_t value, PRINT_Alignment Alignment, char result[4]);

/* Print integer
 *
 * @ value must be less then    100
 * @ value must be bigger then -100
 */
void PRINT_Integer(int16_t value, PRINT_Alignment Alignment, char result[5]);

/* Print unsigned integer value as the decimal value with one digit after decimal point
 *
 * @ value must be less then   1000
 * @ value must be bigger then 0
 */
void PRINT_UnsignedDecimal1Place(uint16_t value, PRINT_Alignment Alignment, char result[5]);

/* Print integer value as the decimal value with one digit after decimal point
 *
 * @ value must be less then    100
 * @ value must be bigger then -100
 */
void PRINT_Decimal1Place(int16_t value, PRINT_Alignment Alignment, char result[6]);

/* Print unsigned integer value as the decimal value with two digits after decimal point
 *
 * @ value must be less then   1000
 * @ value must be bigger then 0
 */
void PRINT_UnsignedDecimal2Place(uint16_t value, char result[5]);

#endif /* __print_h */

/* end of print.h */
