#include "log.h"

void init_log(const char* log_content) {
    /*aslclient log_client;*/
    /*int cause_an_error = open("/fictitious_file", O_RDONLY, 0);*/
    /*log_client = asl_open("LogIt", "The LogIt Facility", ASL_OPT_STDERR);*/
    /*asl_log(log_client, NULL, ASL_LEVEL_EMERG, "This is a dumb test:Error %m:%d", 42);*/
    /*asl_close(log_client);*/
    int cause_an_error = open("/fictitious_file", O_RDONLY, 0); //sets errno to ENOENT
    openlog("LogIt", (LOG_CONS|LOG_PERROR|LOG_PID), LOG_DAEMON);
    syslog(LOG_EMERG, log_content, 0);
    closelog();
}


