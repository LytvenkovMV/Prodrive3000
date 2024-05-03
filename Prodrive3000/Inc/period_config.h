


#ifndef __period_config_h
#define __period_config_h



/* HMI task period in milliseconds
 *
 * @lower limit None
 * @upper limit 5
 */
#define PERIOD_CONF_HMI_TASK_MS					(4)



/* Motor task period in milliseconds
 *
 * @lower limit 10
 * @upper limit None
 */
#define PERIOD_CONF_MOTOR_TASK_MS				(20)



/* Display updating period in milliseconds
 *
 * @lower limit None
 * @upper limit None
 */
#define PERIOD_CONF_DISPLAY_UPDATING_MS			(160)



/* Motor data handling period in milliseconds
 *
 * @lower limit PERIOD_CONF_MOTOR_TASK_MS
 * @upper limit None
 */
#define PERIOD_CONF_MOTOR_DATA_HANDLING_MS		(40)



/* Currents sending period in milliseconds
 *
 * @lower limit None
 * @upper limit PERIOD_CONF_MOTOR_TASK_MS
 */
#define PERIOD_CONF_CURRENTS_SENDING_MS			(10)



/* Currents updating period in milliseconds
 *
 * @lower limit None
 * @upper limit None
 */
#define PERIOD_CONF_CURRENTS_UPDATING_MS		(200)



/* Motor over heating protection period in milliseconds
 *
 * @lower limit PERIOD_CONF_MOTOR_TASK_MS
 * @upper limit None
 */
#define PERIOD_CONF_MOTOR_OVERHEATING_PROT_MS	(1000)



/* Broken phase protection period in milliseconds
 *
 * @lower limit PERIOD_CONF_MOTOR_TASK_MS
 * @upper limit None
 */
#define PERIOD_CONF_BROKEN_PHASE_PROT_MS		(1000)



#endif /* __period_config_h */

/* end of period_config.h */
