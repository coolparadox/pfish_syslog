/* cli_syslogger - CLI exerciser of the pfish_syslog library. */

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <argp.h>
#include <syslog.h>

#define DEBUGGING
#include <pilot_fish/syslog.h>

/* 
 * Command line argument parsing. 
 */

const char *argp_program_version = PACKAGE_VERSION;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

static char doc[] = "pfish_logger -- CLI exerciser for the pfish_syslog library.\vThis routine logs MESSAGE, with syslog priority level LEVEL, to syslog facility FACILITY.\n\nLEVEL = 'EMERG', 'ALERT', 'CRIT', 'ERR', 'WARNING', 'NOTICE', 'INFO', 'DEBUG'.\n\nFACILITY = 'USER', 'MAIL', 'DAEMON', 'AUTH', 'SYSLOG', 'LPR', 'NEWS', 'UUCP', 'CRON', 'AUTHPRIV', 'FTP', 'LOCAL0', 'LOCAL1', 'LOCAL2', 'LOCAL3', 'LOCAL4', 'LOCAL5', 'LOCAL6', 'LOCAL7'.\n";

static char args_doc[] = "MESSAGE";

static struct argp_option options[] = {

	{"facility", 'f', "FACILITY",  0, "facility of the message (default = 'USER').", 0 },
	{"name", 'n', "NAME",  0, "name of the caller function (default = 'main').", 0 },
	{"level", 'l', "LEVEL",  0, "priority level of the message.", 0 },
	{ 0 }

};

struct arguments {

	char *facility;
	char *name;
	char *level;
	char *message;

};


static error_t parse_opt (int key, char *arg, struct argp_state *state) {

	struct arguments *arguments = state->input;

	switch (key) {

		case 'f':

			arguments->facility = arg;
			break;

		case 'n':

			arguments->name = arg;
			break;

		case 'l':

			arguments->level = arg;
			break;

		case ARGP_KEY_ARG:

			switch (state->arg_num) {

				case 0:
					arguments->message = arg;
					break;

				default:

					argp_usage (state);

			}
			break;

		case ARGP_KEY_END:

			if (state->arg_num < 1) {

				argp_usage (state);

			}
			break;

		default:

			return ARGP_ERR_UNKNOWN;

	};

	return (0);

};

static struct argp argp = { options, parse_opt, args_doc, doc };


/* 
 * The portal. 
 */

#define SUCCESS return (EXIT_SUCCESS)
#define FAILURE return (EXIT_FAILURE)

#define SAY(LEVEL,FORMAT,...) \
	\
	fprintf (stderr, "%s: %s: " FORMAT "\n", argv[0], #LEVEL, ##__VA_ARGS__)

int main (int argc, char **argv) {

	struct arguments arguments;	// Arguments given in the command line.

	int level;	// Syslog priority level of the message.
	int facility;	// Syslog facility of the message.

	/*
	 * Get command line arguments.
	 */

	memset (&arguments, 0, sizeof (struct arguments));
	argp_parse (&argp, argc, argv, 0, 0, &arguments);

	/*
	 * Parse log message.
	 */

	if ((strlen (arguments.message)) == 0) {

		SAY (WARNING, "message has zero length.");

	}

	/*
	 * Parse function name.
	 */

	if (arguments.name == NULL) {

		arguments.name = "main";

	}
	else if ((strlen (arguments.name)) == 0) {

		SAY (WARNING, "function name has zero length.");

	}

	/*
	 * Parse priority level.
	 */

	if (arguments.level == NULL) {

		SAY (CRIT, "missing priority level.");
		FAILURE;

	}

#define TEST_LEVEL(LEVEL) \
	\
	else if ((strcmp (arguments.level, #LEVEL)) == 0) { \
		\
		level = LOG_##LEVEL; \
		\
	}

	TEST_LEVEL (EMERG)
	TEST_LEVEL (ALERT)
	TEST_LEVEL (CRIT)
	TEST_LEVEL (ERR)
	TEST_LEVEL (WARNING)
	TEST_LEVEL (NOTICE)
	TEST_LEVEL (INFO)
	TEST_LEVEL (DEBUG)

#undef TEST_LEVEL

	else {

		SAY (CRIT, "unknown priority level '%s'.", arguments.level);
		FAILURE;

	}

	/*
	 * Parse facility.
	 */

	if (arguments.facility == NULL) {

		facility = LOG_USER;

	}

#define TEST_FACILITY(FACILITY) \
	\
	else if ((strcmp (arguments.facility, #FACILITY)) == 0) { \
		\
		facility = LOG_##FACILITY; \
		\
	}

	TEST_FACILITY (USER)
	TEST_FACILITY (MAIL)
	TEST_FACILITY (DAEMON)
	TEST_FACILITY (AUTH)
	TEST_FACILITY (SYSLOG)
	TEST_FACILITY (LPR)
	TEST_FACILITY (NEWS)
	TEST_FACILITY (UUCP)
	TEST_FACILITY (CRON)
	TEST_FACILITY (AUTHPRIV)
	TEST_FACILITY (FTP)
	TEST_FACILITY (LOCAL0)
	TEST_FACILITY (LOCAL1)
	TEST_FACILITY (LOCAL2)
	TEST_FACILITY (LOCAL3)
	TEST_FACILITY (LOCAL4)
	TEST_FACILITY (LOCAL5)
	TEST_FACILITY (LOCAL6)
	TEST_FACILITY (LOCAL7)

#undef TEST_FACILITY

	else {

		SAY (CRIT, "unknown facility '%s'.", arguments.facility);
		FAILURE;

	}

	/*
	 * Exercise the library.
	 */

	pfish_syslog_init (facility, LOG_PERROR | LOG_PID);
	setlogmask (LOG_UPTO (LOG_DEBUG));
	pfish_syslog (level, arguments.name, arguments.message);

	/*
	 * The end.
	 */

	SUCCESS;

}

#undef SAY

#undef FAILURE
#undef SUCCESS

