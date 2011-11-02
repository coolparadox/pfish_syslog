## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

nobase_include_HEADERS = pilot_fish/syslog.h pilot_fish/syslog_macros.h

lib_LTLIBRARIES = libpfish_syslog.la
libpfish_syslog_la_SOURCES = pilot_fish/syslog.h pfish_syslog.c
libpfish_syslog_la_LDFLAGS = -version-info 0:0:0

bin_PROGRAMS = pfish_syslog_library_info pfish_logger

pfish_syslog_library_info_SOURCES = pilot_fish/syslog.h library_info.c
pfish_syslog_library_info_LDADD = -lpfish_syslog

pfish_logger_SOURCES = logger.c
pfish_logger_LDADD = -lpfish_syslog

MAINTAINERCLEANFILES = INSTALL Makefile.in aclocal.m4 config.guess config.sub config.h.in configure depcomp install-sh missing ltmain.sh *~ *.tar.*

maintainer-clean-local:
	-rm -rf m4

