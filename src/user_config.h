/*===================================================.======================================================*/
/*                                             FILE DESCRIPTION												*/
/*==========================================================================================================*/
/**
* @file		: user_config.h
* @author	: ChathurangaD
* @date		: 29 May 2019
*
* @brief	: Configuration that will be available to user to edit.
*
* @note		: Initial draft
*
*/

#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

/*===================================================.======================================================*/
/*												 REFERENCES													*/
/*==========================================================================================================*/

/*===================================================.======================================================*/
/*                                              DEFINITIONS                                                 */
/*==========================================================================================================*/
#ifndef TRUE
#define TRUE		(1)
#endif
#ifndef FALSE
#define FALSE		(0)
#endif

#define __DEBUG__
#define LOG_ENABLED		    (TRUE)
#define LOGGER_UART		    (Serial)
#define LOG_TAG             "[LOG]"

#define FW_VERSION          "1.00.5"

#define TIMEOUT_PROVISIONING_GAP        (20)    /* < in Seconds */
#define TIMEOUT_ATTEND_TAP_RESPONSE    (5)    /* < in Seconds */

#define RETRANSMIT_PROVISIONING         (5)

#define RSSI_UPDATE_INTERVAL            (20)      /* < in seconds */
#define TOUCH_CHECK_INTERVAL            (20)      /* < in milliseconds */

#endif //__USER_CONFIG_H__
