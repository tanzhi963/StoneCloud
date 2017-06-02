#ifndef USER_H
#define USER_H

#include <string>
#include <pthread.h>


using namespace std;


class user 
{
public:
	//构造与析构函数
	user();
	~user();


	//类的方法
	char checkUserNamePassword(string _name,string _password);
	char returnChar(unsigned char _data);

	//类的属性封装函数
	void setSocketid(int _iSocketid);
	int getSocketid();
	void setTid(pthread_t _tid);
	int getTid();
	void setStatus(int _status);
	int getStatus();
	void setProtocol(char _protocol);
	char getProtocol();
	void setUserid(unsigned int _userID);
	unsigned int getUserid();
	void setClientVersion(unsigned int _clientVersion);
	unsigned int getClientVersion();

	
private:
	
//	string m_strName;
	int m_iSocketid;						//用户socket标识符
	pthread_t m_pTid;						//该用户的线程ID
	int m_iStatus;							//用户登录状态
	char m_cProtocol;						//通讯版本号
	unsigned int m_iUserID;					//用户唯一标识符
	unsigned int m_iClientVersion;			//客户端版本号
	
};




#endif