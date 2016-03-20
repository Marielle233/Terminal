#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>

pid_t exec_command(char *command);
void remove_substring(char *s, const char *toremove);

#endif
