#include <iostream>

#include "socket_user.h"
#include "user.h"

using namespace std;


void* socket_user_thread(void *arg)
{
	user *user_new = (user *)arg;
	cout << user_new->get_m_iUser_socket_ID() << endl;
}