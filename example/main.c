#include <stdio.h>
#include <stdlib.h>
#include "../log.c"

int main(int argc, char const *argv[]) {

	int i, j, k = 0, l = 1;

	logfile_t *log_for = logfile_create( "for", MICROTIMER );
	logfile_t *log_while = logfile_create( "while", MICROTIMER );

	while( l ) {

		log_entry_start( log_for );
		for ( i = 0; i < k; i++ ) {
			printf("This is an algorithm that does something similar that is within the while-loop. " );
			printf("But this algorithm isn't that effective. ");
			printf("It just do much more work.\n");
		}
		log_entry_end( log_for, k, i );

		log_entry_start( log_while );
		j = 0;
		while( j < k ) {
			j++;
			printf("This is an algorithm that does something similar that is within the for-loop.\n" );
		}
		log_entry_end( log_while, k, j );

		if ( k >= 1000 )
			l = 0;
		else
			k += 100;

	}

	logfile_avg( log_for );
	logfile_avg( log_while );

	logfile_destroy( log_for );
	logfile_destroy( log_while );


	return 0;
}