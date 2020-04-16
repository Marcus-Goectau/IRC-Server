/*
 * config.h
 * CS3337
 * Written by: Marcus Goeckner
 * 4/15/2020
 *
 * Header file for configuration file tools
*/

#ifndef IRC_CONFIG_H
#define IRC_CONFIG_H

void config_parseLine(char *buffer);

void config_readConfigFile(char *file);

#endif //IRC_CONFIG_H
