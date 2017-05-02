#ifndef SOCKET_USER
#define SOCKET_USER


void* socket_logining_user_thread(void *arg);
void* socket_user_thread(void *arg);
int command_analysis(char *command);

#endif