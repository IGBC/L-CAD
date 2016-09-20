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

void do_log(char* module, int line, char* level, char* colour, char* message, ... );

#define LOG_FATAL(LEVEL,  ... ) {}
#define LOG_CRITICAL(LEVEL,  ... ) {}
#define LOG_ERROR(LEVEL,  ... ) {}
#define LOG_WARNING(LEVEL,  ... ) {}
#define LOG_INFO1(LEVEL,  ... ) {}
#define LOG_INFO2(LEVEL,  ... ) {}
#define LOG_INFO3(LEVEL,  ... ) {}
#define LOG_TRACE(LEVEL,  ... ) {}
#define LOG_DEBUG(LEVEL,  ... ) {}

#if LOGLEVEL >= FATAL
	#undef LOG_FATAL
	#define LOG_FATAL(LEVEL, ... ) { do_log(LOGMODULE, __LINE__, "FATAL", RED, __VA_ARGS__); }
#endif
#if LOGLEVEL >= CRITICAL
	#undef LOG_CRITICAL
	#define LOG_CRITICAL(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "CRITICAL", RED, __VA_ARGS__); }
#endif
#if LOGLEVEL >= ERROR
	#undef LOG_ERROR
	#define LOG_ERROR(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "ERROR", MAG, __VA_ARGS__); }
#endif
#if LOGLEVEL >= WARNING
	#undef LOG_WARNING
	#define LOG_WARNING(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "WARNING", YEL, __VA_ARGS__); }
#endif
#if LOGLEVEL >= INFO1
	#undef LOG_INFO1
	#define LOG_INFO1(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "INFO1", GRN, __VA_ARGS__); }
#endif
#if LOGLEVEL >= INFO2
	#undef LOG_INFO2
	#define LOG_INFO2(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "INFO2", GRN, __VA_ARGS__); }
#endif
#if LOGLEVEL >= INFO3
	#undef LOG_INFO3
	#define LOG_INFO3(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "INFO3", GRN, __VA_ARGS__); }
#endif
#if LOGLEVEL >= TRACE
	#undef LOG_TRACE
	#define LOG_TRACE(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "TRACE", CYN, __VA_ARGS__); }
#endif
#if LOGLEVEL >= DEBUG
	#undef LOG_DEBUG
	#define LOG_DEBUG(LEVEL,  ... ) { do_log(LOGMODULE, __LINE__, "DEBUG", CYN, __VA_ARGS__); }
#endif*/


/* formal usage LOG(LEVEL, MESSAGE, ARGS */
#define LOG(LEVEL, ... ) LOG_##LEVEL(LEVEL, __VA_ARGS__ )
