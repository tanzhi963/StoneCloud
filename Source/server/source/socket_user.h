#ifndef SOCKET_USER
#define SOCKET_USER

#include <string>

void* socket_user_thread(void *arg);
int command_analysis(char *command);

#endif