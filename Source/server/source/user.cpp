#include <iostream>
#include <pthread.h>
#include "user.h"
#include "socket_user.h"

using namespace std;

user::user(int _iUser_socket_ID)
{
	cout << "user object created !" << endl;
	// this -> set_m_iUser_socket_ID(_iUser_socket_ID);
	// //每一个用户创建一个线程，此线程仅归该用户所有
	// int create_user_thread_err = pthread_create(&m_pUsertid,NULL,socket_user_thread,(void*)this);
}

user::~user()
{
	cout << "user object be free !" << endl;
}



