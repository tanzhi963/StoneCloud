#ifndef USER_H
#define USER_H

#include <string>
#include <pthread.h>

class user
{
public:
	user();
	~user();
	void set_m_iUserID(unsigned int _iUserID);
	void set_m_iUser_socket_ID(int _iUser_socket_ID);
	unsigned int get_m_iUserID();
	int get_m_iUser_socket_ID();
	int create_new_users_thread(user *p_user);
	int get_m_pUsertid();
	
private:
	
//	string m_strName;
	unsigned int m_iUserID;						//用户ID
	int m_iUser_socket_ID;						//用户socket标识符
	pthread_t m_pUsertid;
	
};


#endif