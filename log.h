#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct logfile {
	FILE 	*f;
	char	*filename;
	unsigned long long t1, t2;
} logfile_t;

logfile_t *logfile_create( char *logfile_name );
void log_entry_start( logfile_t *logfile );
void log_entry_end( logfile_t *logfile, int idx, int entries );
void logfile_avg( logfile_t *logfile );
void logfile_destroy( logfile_t *logfile );

#endif