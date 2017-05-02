#include <iostream>
#include <pthread.h>

#include "logining_user.h"
#include "socket_user.h"

using namespace std;

//构造函数
logining_user::logining_user(int _iSocketid)
{
	cout << "Logining user object created !" << endl;
	this -> set_socketid(_iSocketid);
	this -> set_status(NOTGETVERSION);
	int create_user_thread_err = pthread_create(&m_pTid,NULL,socket_logining_user_thread,(void*)this);
}

logining_user::~logining_user()
{

}


void logining_user::set_socketid(int _iSocketid)
{
	m_iSocket_ID = _iSocketid;
}

int logining_user::get_socketid()
{
	return m_iSocket_ID;
}

int logining_user::get_tid()
{
	return m_pTid;
}

void logining_user::set_status(int _status)
{
	m_iStatus = _status;
}

int logining_user::get_status()
{
	return m_iStatus;
}

void logining_user::set_protocol(char _protocol)
{
	m_cProtocol = _protocol;
}

char logining_user::get_protocol()
{
	return m_cProtocol;
}