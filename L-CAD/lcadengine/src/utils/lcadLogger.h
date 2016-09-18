#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#ifndef LOGMODULE
#define LOGMODULE "UNKNOWN @" __FILE__
#endif

#define FATAL 0
#define CRITICAL 1
#define ERROR 2
#define WARNING 3
#define INFO1 4
#define INFO2 5
#define INFO3 6
#define TRACE 7
#define DEBUG 8

#define LOGLEVEL DEBUG

#define LOGFILE "lcad.log"
#define STDOUT 1

#define RED   "\x1B[31m"
#define ORG   ""
#define YEL   "\x1B[33m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define DO_LOG(LEVEL, COLOUR, MESSAGE) { \
	struct timeval curTime; \
	gettimeofday(&curTime, NULL); \
	int milli = curTime.tv_usec; \
	char buffer [1000]; \
	struct tm *local = localtime(&curTime.tv_sec); \
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", local); \
	char currentTime[1000] = ""; \
	sprintf(currentTime, "%s.%d", buffer, milli); \
	if(STDOUT) \
		printf("%s ["COLOUR #LEVEL RESET"] ["LOGMODULE":%i]: "MESSAGE"\n", currentTime, __LINE__);\
	if (LOGFILE) { \
		FILE * pFile;\
		pFile = fopen (LOGFILE,"a");\
		if (pFile!=NULL) {\
			fprintf (pFile, "%s ["COLOUR #LEVEL RESET"] ["LOGMODULE":%i]: "MESSAGE"\n", currentTime, __LINE__);\
			fclose (pFile);\
		} else {\
			printf("%s ["COLOUR  "LOGGER" RESET"] ["RED "LOGGER" RESET"]: "RED "ERROR LOGGING TO FILE" RESET"\n", currentTime); \
		} \
	} \
}

#define LOG_FATAL(MESSAGE) {}
#define LOG_CRITICAL(MESSAGE) {}
#define LOG_ERROR(MESSAGE) {}
#define LOG_WARNING(MESSAGE) {}
#define LOG_INFO1(MESSAGE) {}
#define LOG_INFO2(MESSAGE) {}
#define LOG_INFO3(MESSAGE) {}
#define LOG_TRACE(MESSAGE) {}
#define LOG_DEBUG(MESSAGE) {}

#if LOGLEVEL >= FATAL
	#undef LOG_FATAL
	#define LOG_FATAL(MESSAGE) DO_LOG(FATAL, RED, MESSAGE)
#endif
#if LOGLEVEL >= CRITICAL
	#undef LOG_CRITICAL
	#define LOG_CRITICAL(MESSAGE) DO_LOG(CRITICAL, RED, MESSAGE)
#endif
#if LOGLEVEL >= ERROR
	#undef LOG_ERROR
	#define LOG_ERROR(MESSAGE) DO_LOG(ERROR, MAG, MESSAGE)
#endif
#if LOGLEVEL >= WARNING
	#undef LOG_WARNING
	#define LOG_WARNING(MESSAGE) DO_LOG(WARNING, YEL, MESSAGE)
#endif
#if LOGLEVEL >= INFO1
	#undef LOG_INFO1
	#define LOG_INFO1(MESSAGE) DO_LOG(INFO1, GRN, MESSAGE)
#endif
#if LOGLEVEL >= INFO2
	#undef LOG_INFO2
	#define LOG_INFO2(MESSAGE) DO_LOG(INFO2, GRN, MESSAGE)
#endif
#if LOGLEVEL >= INFO3
	#undef LOG_INFO3
	#define LOG_INFO3(MESSAGE) DO_LOG(INFO3, GRN, MESSAGE)
#endif
#if LOGLEVEL >= TRACE
	#undef LOG_TRACE
	#define LOG_TRACE(MESSAGE) DO_LOG(TRACE, CYN, MESSAGE)
#endif
#if LOGLEVEL >= DEBUG
	#undef LOG_DEBUG
	#define LOG_DEBUG(MESSAGE) DO_LOG(DEBUG, CYN, MESSAGE)
#endif

#define LOG(LEVEL, MESSAGE) LOG_##LEVEL(MESSAGE)
