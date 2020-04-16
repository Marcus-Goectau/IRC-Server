/*
 * config.c
 * CS3337
 * Written by: Marcus Goeckner
 * 4/15/2020
 *
 * Reads in and parses config file for server settings
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "client_handler.h"
#include "logger.h"
#include <bits/types/FILE.h>

void leftShift(char *string) {
    int i;
    for (i = 1; i < strlen(string); i++) {
        string[i - 1] = string[i];
    }
}

void config_parseLine(char *buffer) {
    char *line = strstr(buffer, "=");
    int len;
    if (line) {
        len = strlen(line);
        leftShift(line);
        if (line[len-1] != '\0' && line[len-2] != '\0') {
            line[len-1] = '\0';
            line[len-2] = '\0';
        }
        if (strncmp(buffer, "LOG_FILE_LOCATION", 17) == 0) {
            logger_log_file_location = malloc(sizeof(line));
            strcpy(logger_log_file_location, line);
        } else if (strncmp(buffer, "LOGGING_LEVEL", 13) == 0) {
            logger_logging_level = atoi(line);
        } else if (strncmp(buffer, "MAX_NUM_CLIENTS", 15) == 0) {
            client_handler_max_connections = atoi(line);
        } else if (strncmp(buffer, "BUFF_SIZE", 9) == 0) {
            client_handler_buffer_size = atoi(line);
        }
    }
}

void config_readConfigFile(char *filename) {
    FILE *file;
    char *line = NULL;
    size_t read = 0;
    file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not open config file");
        logger_write("ERROR: Could not open config file");
        return;
    }
    while ((read = getline(&line, &read, file)) != -1) {
        config_parseLine(line);
    }
    fclose(file);
}

