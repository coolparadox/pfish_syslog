/*
 * pilot_fish/syslog_macros.h
 * Useful wrappers of pfish_syslog().
 */

#ifndef FILE_PFISH_SYSLOG_MACROS_SEEN
#define FILE_PFISH_SYSLOG_MACROS_SEEN


/*
 * Syslog main logger macro.
 * Almost the same as pfish_syslog(), with the advantage of not having to fill the function name by hand.
 *
 * @param[in] LEVEL syslog level of the message, see syslog(3).
 * @param[in] FORMAT format string (like in printf) of the log message.
 * @param[in] ... optional arguments for the format string (like in printf).
 */

#define PFISH_SYSLOG(LEVEL,FORMAT,...) pfish_syslog (LEVEL, __FUNCTION__, FORMAT, ##__VA_ARGS__)


/*
 * Syslog specialized logger macros.
 * These encapsulate the various priority levels, and are the recommended way to syslog things through this library.
 */

#define EMERG(FORMAT,...) PFISH_SYSLOG (LOG_EMERG, FORMAT, ##__VA_ARGS__)
#define ALERT(FORMAT,...) PFISH_SYSLOG (LOG_ALERT, FORMAT, ##__VA_ARGS__)
#define CRIT(FORMAT,...) PFISH_SYSLOG (LOG_CRIT, FORMAT, ##__VA_ARGS__)
#define ERR(FORMAT,...) PFISH_SYSLOG (LOG_ERR, FORMAT, ##__VA_ARGS__)
#define WARNING(FORMAT,...) PFISH_SYSLOG (LOG_WARNING, FORMAT, ##__VA_ARGS__)
#define NOTICE(FORMAT,...) PFISH_SYSLOG (LOG_NOTICE, FORMAT, ##__VA_ARGS__)
#define INFO(FORMAT,...) PFISH_SYSLOG (LOG_INFO, FORMAT, ##__VA_ARGS__)
#ifdef DEBUGGING
#define DEBUG(FORMAT,...) PFISH_SYSLOG (LOG_DEBUG, FORMAT, ##__VA_ARGS__)
#else
#define DEBUG(FORMAT,...)
#endif	// DEBUGGING


/*
 * Log the most recent C library error with ERR priority level.
 */

#define ERRNO_ERR if (errno != 0) ERR ("%s", strerror (errno))


#endif	// FILE_PFISH_SYSLOG_MACROS_SEEN

