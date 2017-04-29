#ifndef USER_H
#define USER_H

#include <string>
#include <pthread.h>

class user
{
public:
	//构造与析构函数
	user(int _iUser_socket_ID);
	~user();


	//类的属性封装函数
	void set_m_iUserID(unsigned int _iUserID);
	void set_m_iUser_socket_ID(int _iUser_socket_ID);
	unsigned int get_m_iUserID();
	int get_m_iUser_socket_ID();
	int get_m_pUsertid();
	
private:
	
//	string m_strName;
	unsigned int m_iUserID;						//用户ID
	int m_iUser_socket_ID;						//用户socket标识符
	pthread_t m_pUsertid;
	
};


#endif