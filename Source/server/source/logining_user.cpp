#include <iostream>
#include <pthread.h>

#include "logining_user.h"
#include "socket_user.h"

using namespace std;

//构造函数
logining_user::logining_user(int _iLogining_user_socket_ID)
{
	cout << "Logining user object created !" << endl;
	this -> set_m_iLogining_user_socket_ID(_iLogining_user_socket_ID);
	int create_user_thread_err = pthread_create(&m_iLogining_user_socket_ID,NULL,socket_user_thread,(void*)this);
}

logining_user::~logining_user()
{

}


void logining_user::set_m_iLogining_user_socket_ID(int _iLogining_user_socket_ID)
{
	m_iLogining_user_socket_ID = _iLogining_user_socket_ID;
}

int logining_user::get_m_iLogining_user_socket_ID()
{
	return m_iLogining_user_socket_ID;
}

int logining_user::get_m_pLogining_usertid()
{
	return m_pLogining_usertid;
}