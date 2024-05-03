


#ifndef __calibration_h
#define __calibration_h

/* Calibration guide
 *
 * @brief 1. Achieve a zero readings by changing zero shift value
 *        2. Inject the current and achieve an accurate reading
 *           by changing coefficient value
 */

/* Zero shifts for IL1 and IL3 channels (integer type) */
#define CALIBRATION_IL1_ZERO_SHIFT				(57)
#define CALIBRATION_IL3_ZERO_SHIFT				(66)

/* Coefficients for IL1 and IL3 channels (float type) */
#define CALIBRATION_IL1_COEFF					(0.013850)
#define CALIBRATION_IL3_COEFF					(0.014125)

#endif /* __calibration_h */

/* end of calibration.h */
