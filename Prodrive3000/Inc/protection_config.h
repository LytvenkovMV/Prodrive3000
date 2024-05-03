


#ifndef __protection_config_h
#define __protection_config_h



/* Over current protection configuration */
/* Limit of the instantaneous current rise */
#define PROT_CONF_CURRENT_RISE_LIMIT		(50)



/* DC voltage protection configuration */
/* DC voltage lower threshold in volts */
#define PROT_CONF_DC_VOLTAGE_LOWER_THRD		(450)

/* DC voltage upper threshold in volts */
#define PROT_CONF_DC_VOLTAGE_UPPER_THRD		(780)

/* DC voltage differential protection threshold */
#define PROT_CONF_DC_DIFFVOLTAGE_THRD		(20)



/* Broken phase protection configuration */
/* Protection minimum operating current in amperes. If current in all phases is less than this minimum value protection doesn't work */
#define PROT_CONF_MIN_OPERATING_CURRENT		(0.2)

/* Current difference threshold in % */
#define PROT_CONF_CURR_DIFFERENCE_THRD		(20)

/* Delay in seconds */
#define PROT_CONF_BROKEN_PHASE_DELAY_S		(10)



/* Drive over heating protection configuration */
/* Over heating temperature */
#define PROT_CONF_DRIVE_OVERHEATING_TEMP	(45)

/* Alarm temperature */
#define PROT_CONF_DRIVE_ALARM_TEMP			(40)

/* Temperature differential protection threshold */
#define PROT_CONF_DIFFTEMP_THRD				(3)



/* Motor over heating protection configuration */
/* Time-current curve multiplier CM = 87.4 * K, where K is in the range from 1 to 30 */
#define PROT_CONF_CURVE_MULTIPLIER			(1048.8)

/* Cooling time constant in seconds */
#define PROT_CONF_COOLING_TIME_CONST_S		(5000)

/* Inverse value of the service factor 1/SF */
#define PROT_CONF_SERVICE_FACTOR_INV		(1)

/* Alarm TCU */
#define PROT_CONF_MOTOR_ALARM_TCU			(95)



#endif /* __protection_config_h */

/* end of protection_config.h */
