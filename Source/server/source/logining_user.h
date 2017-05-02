/************************************************
/*
/*用户连接服务端，在登录前的状态
/*
************************************************/



#ifndef LOGINING_USER
#define LOGINING_USER


class logining_user 
{
public:
	//构造与析构函数
	logining_user(int _iLogining_user_socket_ID);
	~logining_user();


	//类的属性封装函数
	void set_m_iLogining_user_socket_ID(int _iLogining_user_socket_ID);
	int get_m_iLogining_user_socket_ID();
	int get_m_pLogining_usertid();
	
private:
	
//	string m_strName;
	int m_iLogining_user_socket_ID;						//用户socket标识符
	pthread_t m_pLogining_usertid;
	
};




#endif
