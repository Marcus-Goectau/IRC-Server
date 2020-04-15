/*
 * logger.h
 * CS3337
 * Written by: Marcus Goeckner
 * 4/14/2020
 *
 * Header file for logging functionalities
*/

#ifndef IRC_LOGGER_H
#define IRC_LOGGER_H

#include <bits/types/FILE.h>

void logger_write(char log_entry[256]);

FILE *logger_log_file;
char logger_log_file_location[256];
int logger_logging_level; //indicates level of logging (w/ 0 = no logging)

#endif //IRC_LOGGER_H
