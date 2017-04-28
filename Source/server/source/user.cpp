#include <iostream>
#include "user.h"
#include "socket_user.h"

using namespace std;

user::user(int _iUser_socket_ID)
{
	cout << "user object created !" << endl;
	this -> set_m_iUser_socket_ID(_iUser_socket_ID);
	//每一个用户创建一个线程，此线程仅归该用户所有
	int create_user_thread_err = pthread_create(&m_pUsertid,NULL,socket_user_thread,(void*)this);
}

user::~user()
{
	cout << "user object be free !" << endl;
}



void user::set_m_iUserID(unsigned int _iUserID)
{
	m_iUserID = _iUserID;
}
void user::set_m_iUser_socket_ID(int _iUser_socket_ID)
{
	m_iUser_socket_ID = _iUser_socket_ID;
}
unsigned int user::get_m_iUserID()
{
	return m_iUserID;
}
int user::get_m_iUser_socket_ID()
{
	return m_iUser_socket_ID;
}

int user::get_m_pUsertid()
{
	return m_pUsertid;
}