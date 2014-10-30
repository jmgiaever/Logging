#include "log.h"
#include <string.h>

/**
 * Opens a logfile from the logfile struct
 **/
static void logfile_open( logfile_t *logfile, char *mode ) {

	if ( logfile->f != NULL )
		fclose( logfile->f );

	logfile->f = fopen( logfile->filename, mode );

	if ( logfile->f == NULL ) {
		printf("Unable ot allocate memory or to open logfile: %s\n", logfile->filename );

		if ( logfile != NULL )
			free( logfile );

		return;

	}

}

/**
 * Get the time
 **/
static unsigned long long gettime( void ) {
    int retval;
    struct timeval tp;
    unsigned long long ctime;

    retval = gettimeofday( &tp, NULL );
    ctime = tp.tv_sec;
    ctime *= 1000000;
    ctime += tp.tv_usec;

    return ctime;

}

/** 
 * When something bad happens.... we end!
 **/
static void fatal_error( char *error_msg ) {
	printf( "Fatal error: %s\n", error_msg );
	exit( 1 );
}

/**
 * Create a log file.
 **/
logfile_t *logfile_create( char *logfile_name ) {

	char buf[1024];

	logfile_t *logfile = ( logfile_t *) malloc( sizeof( logfile_t ) );

	if ( logfile == NULL )
		goto error;

	snprintf(buf, sizeof buf, "Logging/logs/%s.data", logfile_name );
	logfile->filename = strdup( buf );

	logfile_open( logfile, "w" );

	return logfile;

	error:

		return NULL;

}

/**
 * Start measuring: Create a log entry
 **/
unsigned long long log_entry_start( logfile_t *logfile ) {
	
	logfile->t1 = gettime();

}

/**
 * End measuring: End a log entry
 **/
void log_entry_end( logfile_t *logfile, int idx, int entries ) {

	int result;

	if ( logfile->t1 == 0.0 )
		fatal_error( "You must start an log entry before ending it." );

	logfile->t2 = gettime();

	if ( entries <= 0 )
		entries = 1;

	result = (int)( logfile->t2 - logfile->t1 ) / entries;

	fprintf( logfile->f, "%d %d\n", idx, result );
	fflush( logfile->f );

	logfile->t1 = 0.0;
	logfile->t2 = 0.0;

}

/**
 * Print avarage time spent for one log,
 * based on all measurements
 **/
void logfile_avg( logfile_t *logfile ) {

	int i = 0, 
		val = 0;
	char *line, *tokenized, *timestamp;
	ssize_t read;
	size_t len = 0;

	logfile_open( logfile, "r" );
	
	printf( "\nEvaluate avg.time from logfile:\n* %s", logfile->filename );

	while( (read = getline(&line, &len, logfile->f )) != -1 ) {

		tokenized = strtok( line, " " );

		while( tokenized != NULL ) {
			timestamp = tokenized;
			tokenized = strtok( NULL, " ");
		}

		val += atoi( timestamp );
		i++;
	}

	logfile_open( logfile, "a" );

	puts( "\n\t\tValue/entries:\t  Avg. time: (microsec.)");
	printf("\tAvg:\t%d/%d \t\t= %f\n", val, i, (float)( (float)val /(float)i ) );

}

/**
 * Destroy logfile: free up memory
 **/
void logfile_destroy( logfile_t *logfile ) {

	if ( logfile == NULL )
		return;

	if ( logfile->f )
		fclose( logfile->f );

	printf( "Logfile stored in: %s\n", logfile->filename );

	free( logfile->filename );
	free( logfile );

}