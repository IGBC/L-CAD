
#include "lcadLogger.h"

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>

void do_log(char* module, int line, char* level, char* colour, char* message, ... ) {
	struct timeval curTime;
	gettimeofday(&curTime, NULL);
	int milli = curTime.tv_usec;
	char buffer [1024];
	struct tm *local = localtime(&curTime.tv_sec);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", local);
	char currentTime[1024] = "";
	sprintf(currentTime, "%s.%d", buffer, milli);
	char format[128];
	sprintf(format, "%s [%s%s%s] [%s:%i]: %s\n", currentTime, colour, level, RESET, module, line, message);
	char output[1024];
	va_list args;
	va_start(args, message);
	vsprintf(output, format, args);
	va_end(args);
	
	if(STDOUT) {
		printf("%s",output);
	}
	if (LOGFILE) {
		FILE * pFile;
		pFile = fopen (LOGFILE,"a");
		if (pFile!=NULL) {
			fprintf(pFile, "%s", output);
			fclose (pFile);
		} else {
			printf("%s [" RED "LOGGER" RESET"] ["RED "LOGGER" RESET"]: "RED "ERROR LOGGING TO FILE" RESET"\n", currentTime);
		}
	}
}

