
#include "lcadLogger.h"

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>

void do_log(int level, char* colour, char* message, ... ) {
	struct timeval curTime;
	gettimeofday(&curTime, NULL);
	int milli = curTime.tv_usec;
	char buffer [1000];
	struct tm *local = localtime(&curTime.tv_sec);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", local);
	char currentTime[1000] = "";
	sprintf(currentTime, "%s.%d", buffer, milli);
	char format[100];
	sprintf(format, "%s [%s%i%s] [%s:%s]: %s\n", currentTime, colour, level, RESET, LOGMODULE, TOSTRING(__LINE__), message);
	if(STDOUT) {
		#if defined __VA_ARGS__
			printf(format);
		#endif
		#if !defined __VA_ARGS__
			printf(format, __VA_ARGS__);
		#endif
	}
	if (LOGFILE) {
		FILE * pFile;
		pFile = fopen (LOGFILE,"a");
		if (pFile!=NULL) {
			#if defined __VA_ARGS__
				fprintf(pFile, format);
			#endif
			#if ! defined _VA_ARGS__
				fprintf(pFile, format, __VA_ARGS__);
			#endif
			fclose (pFile);
		} else {
			printf("%s [" RED "LOGGER" RESET"] ["RED "LOGGER" RESET"]: "RED "ERROR LOGGING TO FILE" RESET"\n", currentTime);
		}
	}
}

