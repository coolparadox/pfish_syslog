/*
 * pilot_fish/syslog.h
 * pilot_fish syslog wrapper library.
 */

#ifndef FILE_PFISH_SYSLOG_SEEN
#define FILE_PFISH_SYSLOG_SEEN


/*
 * Library info structure.
 */

struct pfish_syslog_library_info {

	char *build_date;		// Date when the library was built.
	char *build_time;		// Time of day when the library was built.
	char *compiler_version;		// Version of the compiled used to build the library.

};

typedef struct pfish_syslog_library_info pfish_syslog_library_info_t;


/*
 * Library info getter.
 * Fills a info structure with static information about the library.
 *
 * param[out] target pointer to a info structure to be filled.
 */

void pfish_syslog_library_info_get (pfish_syslog_library_info_t *target);


/*
 * Syslog initializer.
 * Configure the global syslog handle structure. 
 * Does not change the current syslog mask, see setlogmask (3).
 *
 * @param[in] syslog_facility syslog facility code, see syslog (3).
 * @param[in] openlog_options opening options of the syslog connection, see openlog (3).
 */

void pfish_syslog_init (int syslog_facility, int openlog_options);


/*
 * Syslog main logger function.
 * This is the most generic syslog call, over which more specialized syslog functions are built.
 *
 * @param[in] level syslog level of the message, see syslog(3).
 * @param[in] function_name name of the current function that generates the log.
 * @param[in] format format string (like in printf) of the log message.
 * @param[in] ... optional arguments for the format string (like in printf).
 */

void pfish_syslog (int level, const char *function_name, const char *format, ...);


#endif	// FILE_PFISH_SYSLOG_SEEN

