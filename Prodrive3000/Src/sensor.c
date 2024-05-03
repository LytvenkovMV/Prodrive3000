
#include "sensor.h"
#include "sensor_config.h"



void SENSOR_CalibrateADC(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2)
{
	HAL_StatusTypeDef Status1 = HAL_ERROR, Status2 = HAL_ERROR;

	/* Calibrate ADC1 */
	do
	{
		Status1 = HAL_ADCEx_Calibration_Start (hadc1);
		osDelay(50);
	}
	while (Status1 != HAL_OK);

	/* Calibrate ADC2 */
	do
	{
		Status2 = HAL_ADCEx_Calibration_Start (hadc2);
		osDelay(50);
	}
	while (Status2 != HAL_OK);
}



void SENSOR_StartADC(SENSOR_ADCvalues *ADCvalues, ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2)
{
	/* Start slave ADC */
	HAL_ADC_Start(hadc2);

	/* Start master ADC */
	HAL_ADCEx_MultiModeStart_DMA(hadc1, (uint32_t *)ADCvalues, 2);
}



void SENSOR_StopADC(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2)
{
	/* Stop master ADC */
	HAL_ADCEx_MultiModeStop_DMA(hadc1);

	/* Stop slave ADC */
	HAL_ADC_Stop(hadc2);
}



void SENSOR_CalculateInstCurrents(SENSOR_ADCvalues *ADCvalues, SENSOR_CurrentsStruct *Currents)
{
	/* If reference voltage is out of range */
	if ((ADCvalues->Uref < SENSOR_UREF_LOWER_LIMIT) || (ADCvalues->Uref > SENSOR_UREF_UPPER_LIMIT))
	{
		Currents->Status = SENSOR_FAIL;
	}
	else
	{
		Currents->Status = SENSOR_OK;

		/* Save previous values */
		Currents->prevIL1 = Currents->currIL1;
		Currents->prevIL3 = Currents->currIL3;

		/* Calculate current values */
		/* The values in relative units, not amperes */
		Currents->currIL1 = ADCvalues->IL1 - ADCvalues->Uref + SENSOR_ADC1_ZERO_SHIFT;
		Currents->currIL3 = ADCvalues->IL3 - ADCvalues->Uref + SENSOR_ADC2_ZERO_SHIFT;
	}
}



void SENSOR_CalculateRMSCurrents(SENSOR_InstCurrents *InstCurrents, float rmsBufferL1[], float rmsBufferL2[], float rmsBufferL3[])
{
	float tempIL1 = 0, tempIL2 = 0, tempIL3 = 0;
	float sumIL1 = 0, sumIL2 = 0, sumIL3 = 0;
	float IL1 = 0, IL2 = 0, IL3 = 0;

	/* Calculate RMS values */
	for (uint16_t i = 0; i < SENSOR_INST_CURR_BUFFER_SIZE; i ++)
	{
		IL1 = InstCurrents->bufferIL1[i] * SENSOR_ADC1_COEFF;
		IL3 = InstCurrents->bufferIL3[i] * SENSOR_ADC2_COEFF;
		IL2 = IL1 + IL3;

		sumIL1 += (IL1 * IL1);
		sumIL2 += (IL2 * IL2);
		sumIL3 += (IL3 * IL3);
	}
	tempIL1 = sqrtf(sumIL1 / SENSOR_RMS_CURR_BUFFER_SIZE);
	tempIL2 = sqrtf(sumIL2 / SENSOR_RMS_CURR_BUFFER_SIZE);
	tempIL3 = sqrtf(sumIL3 / SENSOR_RMS_CURR_BUFFER_SIZE);

	/* Shift RMS current buffers to the left */
	for (uint16_t i = 0; i < (SENSOR_RMS_CURR_BUFFER_SIZE - 1); i ++)
	{
		rmsBufferL1[i] = rmsBufferL1[i + 1];
		rmsBufferL2[i] = rmsBufferL2[i + 1];
		rmsBufferL3[i] = rmsBufferL3[i + 1];
	}

	/* Copy calculated values to the last buffers members */
	rmsBufferL1[SENSOR_RMS_CURR_BUFFER_SIZE - 1] = tempIL1;
	rmsBufferL2[SENSOR_RMS_CURR_BUFFER_SIZE - 1] = tempIL2;
	rmsBufferL3[SENSOR_RMS_CURR_BUFFER_SIZE - 1] = tempIL3;
}



float SENSOR_CalculateMeanCurrent(float buffer[], uint16_t const bufferSize)
{
	float sum = 0, meanValue = 0;

	for (uint16_t i = 0; i < bufferSize; i ++)
	{
		sum += buffer[i];
	}

	meanValue = sum / bufferSize;

	return meanValue;
}



float SENSOR_CalculateMeanVoltage(uint16_t buffer[], uint16_t const bufferSize)
{
	float sum = 0, meanValue = 0;

	for (uint16_t i = 0; i < bufferSize; i ++)
	{
		sum += buffer[i];
	}

	meanValue = sum / bufferSize;

	return meanValue;
}



int8_t SENSOR_CalculateMeanTemperature(int8_t buffer[], uint16_t const bufferSize)
{
	float sum = 0, temp = 0;
	int8_t meanValue = 0;

	for (uint16_t i = 0; i < bufferSize; i ++)
	{
		sum += (float)buffer[i];
	}

	temp = sum / bufferSize;

	meanValue = (int8_t)roundf(temp);

	return meanValue;
}



uint8_t SENSOR_CalcCRC7(char const message[4])
{
	uint8_t crc = 0, CRC7_POLY = 0x89;

	for (uint8_t i = 0; i < 4; i++)
	{
		crc = crc ^ message[i];

		for (uint8_t j = 0; j < 8; j++)
		{
		  if (crc & 1)crc = crc ^ CRC7_POLY;

		  crc = crc >> 1;
		}
	}

	return crc;
}



SENSOR_Status SENSOR_CheckRXData(SENSOR_RXData *Data)
{
	uint8_t crc = 0;
	char message[4];

	message[0] = Data->byte1;
	message[1] = Data->byte2;
	message[2] = Data->byte3;
	message[3] = Data->byte4;

	/* Calculate CRC7 */
	crc = SENSOR_CalcCRC7(message);

	/* If calculated CRC7 and CRC7 in the RX data are equal, return OK */
	if (crc == Data->crc) return SENSOR_OK;

	return SENSOR_FAIL;
}



void SENSOR_HandleRXData(SENSOR_RXData *RXData, uint16_t voltageDCBuffer[], int8_t tempRectifierBuffer[], int8_t tempInverterBuffer[])
{
	/* Shift buffers to the left */
	for (uint16_t i = 0; i < (SENSOR_VOLTAGE_DC_BUFFER_SIZE - 1); i ++)
	{
		voltageDCBuffer[i] = voltageDCBuffer[i + 1];
	}

	for (uint16_t i = 0; i < (SENSOR_TEMPERATURE_BUFFER_SIZE - 1); i ++)
	{
		tempRectifierBuffer[i] = tempRectifierBuffer[i + 1];
		tempInverterBuffer[i] = tempInverterBuffer[i + 1];
	}

	/* Copy received values to the last buffers members */
	voltageDCBuffer[SENSOR_VOLTAGE_DC_BUFFER_SIZE - 1] = (uint16_t)(((RXData->byte1) << 8) | (RXData->byte2));

	tempRectifierBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE - 1] = (int8_t)RXData->byte3;
	tempInverterBuffer[SENSOR_TEMPERATURE_BUFFER_SIZE - 1] = (int8_t)RXData->byte4;
}



void SENSOR_GetCharValue(uint8_t number, SENSOR_HMIValues *Values, char result[12])
{
	SENSOR_Type Type;
	int16_t value = 0;

	/* Get type, status and value */
	switch (number)
	{
	case 1:
	{
		Type = SENSOR_CONF_SENSOR01_TYPE;
		value = Values->voltageOutput;
	}
	break;

	case 2:
	{
		Type = SENSOR_CONF_SENSOR02_TYPE;
		value = Values->currentL1;
	}
	break;

	case 3:
	{
		Type = SENSOR_CONF_SENSOR03_TYPE;
		value = Values->currentL2;
	}
	break;

	case 4:
	{
		Type = SENSOR_CONF_SENSOR04_TYPE;
		value = Values->currentL3;
	}
	break;

	case 5:
	{
		Type = SENSOR_CONF_SENSOR05_TYPE;
		value = Values->voltageDC;
	}
	break;

	case 6:
	{
		Type = SENSOR_CONF_SENSOR06_TYPE;
		value = Values->motorTCU;
	}
	break;

	case 7:
	{
		Type = SENSOR_CONF_SENSOR07_TYPE;
		value = Values->tempRectifier;
	}
	break;

	case 8:
	{
		Type = SENSOR_CONF_SENSOR08_TYPE;
		value = Values->tempInverter;
	}
	break;

	default:
	{
		strcpy(result, "");
		return;
	}
	}

	/* Convert to char */
	switch (Type)
	{
		case SENSOR_INTEGER_PERCENT:
		{
			PRINT_UnsignedInteger((uint16_t)value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_DEGREE_UNIT);
		}
		break;

		case SENSOR_INTEGER_DEGREE:
		{
			PRINT_Integer(value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_DEGREE_UNIT);
		}
		break;

		case SENSOR_1_DECIMAL_DEGREE:
		{
			PRINT_Decimal1Place(value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_DEGREE_UNIT);
		}
		break;

		case SENSOR_INTEGER_VOLT:
		{
			PRINT_UnsignedInteger((uint16_t)value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_VOLT_UNIT);
		}
		break;

		case SENSOR_1_DECIMAL_VOLT:
		{
			PRINT_UnsignedDecimal1Place((uint16_t)value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_VOLT_UNIT);
		}
		break;

		case SENSOR_INTEGER_AMPERE:
		{
			PRINT_UnsignedInteger((uint16_t)value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_AMPERE_UNIT);
		}
		break;

		case SENSOR_1_DECIMAL_AMPERE:
		{
			PRINT_UnsignedDecimal1Place((uint16_t)value, PRINT_RIGHT_ALIGNMENT, result);
			strcat(result, SENSOR_CONF_AMPERE_UNIT);
		}
		break;

		case SENSOR_2_DECIMAL_AMPERE:
		{
			PRINT_UnsignedDecimal2Place((uint16_t)value, result);
			strcat(result, SENSOR_CONF_AMPERE_UNIT);
		}
		break;

		default:
		{
			strcpy(result, "?????");
		}
	}
}
