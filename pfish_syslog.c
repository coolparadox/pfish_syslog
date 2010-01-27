/* pfish_syslog.c - pilot_fish syslog wrapper library. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

#include <pilot_fish/syslog.h>


void pfish_syslog_library_info_get (pfish_syslog_library_info_t *target) {

	target->build_date = __DATE__;
	target->build_time = __TIME__;
	target->compiler_version = __VERSION__;

}


struct pfish_syslog_handle {

	int facility;	// parameter 'FACILITY' of openlog().
	int options;	// parameter 'OPTION' of openlog().

};

typedef struct pfish_syslog_handle pfish_syslog_handle;

pfish_syslog_handle _pfish_syslog_handle;


void pfish_syslog_init (int syslog_facility, int openlog_options) {

	_pfish_syslog_handle.facility = syslog_facility;
	_pfish_syslog_handle.options = openlog_options;

}


char *pfish_syslog_level_string (int level) {

	switch (level) {

		case LOG_EMERG: return ("EMERG");
		case LOG_ALERT: return ("ALERT");
		case LOG_CRIT: return ("CRIT");
		case LOG_ERR: return ("ERR");
		case LOG_WARNING: return ("WARNING");
		case LOG_NOTICE: return ("NOTICE");
		case LOG_INFO: return ("INFO");
		case LOG_DEBUG: return ("DEBUG");
		default: return ("unknown priority level");

	}
	return (NULL);

}


void pfish_syslog (int level, const char *function_name, const char *format, ...) {

#define BUFSIZE 0x400

	char format_buffer[BUFSIZE];	// Format string of the full message.
	int sn_size;	// Format buffer overflow detector.
	va_list format_args;	// Optional arguments of this function.

	/* Prepend hooks for the priority level and function name into the format string. */

	if ((sn_size = snprintf (format_buffer, BUFSIZE, "(%s) %s: %s", pfish_syslog_level_string (level), function_name, format)) >= BUFSIZE) {

		/* Format buffer overflow. */

		openlog (NULL, LOG_PERROR, LOG_SYSLOG);
		syslog (LOG_ALERT, "(%s) %s: format buffer overflow by %u octets.", pfish_syslog_level_string (LOG_ALERT), __FUNCTION__, sn_size - BUFSIZE + 1);
		closelog ();

	}

	/* Call syslog. */

	va_start (format_args, format);
	openlog (NULL, _pfish_syslog_handle.options, _pfish_syslog_handle.facility);
	vsyslog (level, format_buffer, format_args);
	closelog ();
	va_end (format_args);

#undef BUFSIZE

}

