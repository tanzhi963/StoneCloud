/************************************************
/*
/*用户连接服务端，在登录前的状态
/*
************************************************/



#ifndef LOGINING_USER
#define LOGINING_USER

#define NOTGETVERSION 0
#define NOTGETUSERPASS 1

class logining_user 
{
public:
	//构造与析构函数
	logining_user(int _iSocketid);
	~logining_user();


	//类的属性封装函数
	void set_socketid(int _iSocketid);
	int get_socketid();
	int get_tid();
	void set_status(int _status);
	int get_status();
	void set_protocol(char _protocol);
	char get_protocol();
	
private:
	
//	string m_strName;
	int m_iSocket_ID;						//用户socket标识符
	pthread_t m_pTid;						//该用户的线程ID
	int m_iStatus;							//用户登录状态
	char m_cProtocol;						//通讯版本号
	
	
};




#endif
