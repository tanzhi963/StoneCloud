#include <iostream>
#include "user.h"

using namespace std;

user::user()
{
	cout << "user object created !" << endl;
}

user::~user()
{
	cout << "user object be free !" << endl;
}

int user::create_new_users_thread(user *p_user)
{
	cout << p_user << endl;
	return 0;
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