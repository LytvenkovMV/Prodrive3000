
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "string.h"
#include "print.h"
#include "math.h"
#include "calibration.h"



#ifndef __sensor_h
#define __sensor_h

/* Instantaneous currents buffers size. Value must be a power of two. Allowed values: 1, 2, 4, 8, 16, 32, 64, 128 */
#define SENSOR_INST_CURR_BUFFER_SIZE				(64)

/* RMS currents buffers size. Value must be a power of two. Allowed values: 1, 2, 4, 8, 16, 32, 64, 128 */
#define SENSOR_RMS_CURR_BUFFER_SIZE					(16)

/* Instantaneous voltage DC buffers size. Value must be a power of two. Allowed values: 1, 2, 4, 8, 16, 32, 64, 128 */
#define SENSOR_VOLTAGE_DC_BUFFER_SIZE				(16)

/* Instantaneous temperature buffers size. Value must be a power of two. Allowed values: 1, 2, 4, 8, 16, 32, 64, 128 */
#define SENSOR_TEMPERATURE_BUFFER_SIZE				(16)

/* ADC coefficients
 *
 * @brief Klpf - coefficient of the low pass filter
 *        Klpf = 1 / A , where
 *        A - attenuation of the low pass filter
 *
 * @brief Kct - current transformer coefficient
 *        Kct = Iprimary / Uadc , where
 *        Iprimary - current in the primary winding of CT, A
 *        Uadc - voltage in the ADC input, V
 *
 * @brief Kconv - conversion coefficient (the weight of the LSB)
 *        Kconv = VDDA / (10 * 2^Nadc) , where
 *        VDDA - analog power supply, mV
 *        Nadc - ADC resolution, bits
 *
 * @brief Kadc - total ADC coefficient
 *        Kadc = Klpf * Kct * Kconv
 */

/* ADC coefficients */
#define SENSOR_ADC1_COEFF					(CALIBRATION_IL1_COEFF)
#define SENSOR_ADC2_COEFF					(CALIBRATION_IL3_COEFF)

/* Zero shifts for ADC1 and ADC2 */
#define SENSOR_ADC1_ZERO_SHIFT				(CALIBRATION_IL1_ZERO_SHIFT)
#define SENSOR_ADC2_ZERO_SHIFT				(CALIBRATION_IL3_ZERO_SHIFT)

/* ADC result limits for Uref */
#define SENSOR_UREF_LOWER_LIMIT				(2000)
#define SENSOR_UREF_UPPER_LIMIT				(3000)

/* Sensor type */
typedef enum
{
	SENSOR_INTEGER_PERCENT,
	SENSOR_INTEGER_DEGREE,
	SENSOR_1_DECIMAL_DEGREE,
	SENSOR_INTEGER_VOLT,
	SENSOR_1_DECIMAL_VOLT,
	SENSOR_INTEGER_AMPERE,
	SENSOR_1_DECIMAL_AMPERE,
	SENSOR_2_DECIMAL_AMPERE
} SENSOR_Type;

/* ADC values */
typedef struct
{
	uint16_t IL1;
	uint16_t IL3;
	uint16_t Uref;
	uint16_t NotUsed;
} SENSOR_ADCvalues;

/* Sensor status */
typedef enum
{
	SENSOR_FAIL,
	SENSOR_OK
} SENSOR_Status;

/* Currents structure */
typedef struct
{
	SENSOR_Status Status;
	int16_t currIL1;
	int16_t currIL3;
	int16_t prevIL1;
	int16_t prevIL3;
} SENSOR_CurrentsStruct;

/* Buffer for instantaneous currents */
typedef struct
{
	SENSOR_Status Status;
	int16_t bufferIL1[SENSOR_INST_CURR_BUFFER_SIZE];
	int16_t bufferIL3[SENSOR_INST_CURR_BUFFER_SIZE];
} SENSOR_InstCurrents;

/* Data received by USART */
typedef struct
{
	char byte1;
	char byte2;
	char byte3;
	char byte4;
	char crc;
} SENSOR_RXData;

/* Sensor values */
typedef struct
{
	float rmsCurrentBufferL1[SENSOR_RMS_CURR_BUFFER_SIZE];
	float rmsCurrentBufferL2[SENSOR_RMS_CURR_BUFFER_SIZE];
	float rmsCurrentBufferL3[SENSOR_RMS_CURR_BUFFER_SIZE];
	float meanCurrentL1;
	float meanCurrentL2;
	float meanCurrentL3;
	uint16_t instVoltageDCBuffer[SENSOR_VOLTAGE_DC_BUFFER_SIZE];
	int8_t instTempRectifierBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE];
	int8_t instTempInverterBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE];
	float meanVoltageDCfloat;
	uint16_t meanVoltageDCint;
	int8_t meanTempRectifier;
	int8_t meanTempInverter;
} SENSOR_Values;

/* Sensor values for HMI */
typedef struct
{
	int16_t voltageOutput;
	int16_t currentL1;
	int16_t currentL2;
	int16_t currentL3;
	int16_t voltageDC;
	int16_t motorTCU;
	int16_t tempRectifier;
	int16_t tempInverter;
} SENSOR_HMIValues;

/* Calibrate ADC */
void SENSOR_CalibrateADC(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2);

/* Start ADC */
void SENSOR_StartADC(SENSOR_ADCvalues *ADCvalues, ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2);

/* Stop ADC */
void SENSOR_StopADC(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2);

/* Calculate instantaneous currents values in relative units (not amperes) */
void SENSOR_CalculateInstCurrents(SENSOR_ADCvalues *ADCvalues, SENSOR_CurrentsStruct *Currents);

/* Calculate RMS currents in amperes multiplied by 100 */
void SENSOR_CalculateRMSCurrents(SENSOR_InstCurrents *InstCurrents, float rmsBufferL1[], float rmsBufferL2[], float rmsBufferL3[]);

/* Calculate mean current from a buffer of RMS currents */
float SENSOR_CalculateMeanCurrent(float buffer[], uint16_t const bufferSize);

/* Calculate mean voltage from a buffer of instantaneous voltages */
float SENSOR_CalculateMeanVoltage(uint16_t buffer[], uint16_t const bufferSize);

/* Calculate mean temperature from a buffer of instantaneous temperatures */
int8_t SENSOR_CalculateMeanTemperature(int8_t buffer[], uint16_t const bufferSize);

/* Check RX data for errors */
SENSOR_Status SENSOR_CheckRXData(SENSOR_RXData *Data);

/* Get sensor values from the RX data */
void SENSOR_HandleRXData(SENSOR_RXData *RXData, uint16_t voltageDCBuffer[], int8_t tempRectifierBuffer[], int8_t tempInverterBuffer[]);

/* Get char representation of the sensor value */
void SENSOR_GetCharValue(uint8_t number, SENSOR_HMIValues *Values, char result[12]);

#endif /* __sensor_h */

/* end of sensor.h */
