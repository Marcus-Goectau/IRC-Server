/*
 * logger.c
 * CS3337
 * Written by: Marcus Goeckner
 * 4/14/2020
 *
 * logger to record events occurring during server operations
*/

#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/// writes to a log file with current time information
/// \param log_entry: The string to be appended to the log file
void logger_write(const char *log_entry) {
    if (logger_logging_level != 0) {
        time_t my_time = time(NULL);
        char *time_str = ctime(&my_time);
        time_str[strlen(time_str)-1] = '\0'; // Build string to display current time of this log entry
        logger_log_file = fopen(logger_log_file_location, "a+");
        if (logger_log_file == NULL) {
            perror("fopen");
            return;
        }
        int write = fprintf(logger_log_file, "%s:\n%s\n", time_str, log_entry);
        if (write < 0) {
            perror("fprintf");
        }
        fclose(logger_log_file);
    }
}

