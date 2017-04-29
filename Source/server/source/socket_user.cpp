#include <iostream>
#include <unistd.h>
#include <string.h>

#include "socket_user.h"
#include "user.h"

using namespace std;

#define RECEIVE_LENGTH 1024


void* socket_user_thread(void *arg)
{
	user *user_new = (user *)arg;				//将对象转换回来
	bool connect_status = 1;					//用来表示用户当前SOCKET连接状态，连接：1；断开：0
	char receive_buff[RECEIVE_LENGTH] = {0};	//存放客户端发送来的指令信息
	int read_lenth_count = 0;					//缓存读取套接字的长度
	string command;
	while(connect_status)						//一直接收指令
	{
		read_lenth_count = read(user_new->get_m_iUser_socket_ID(),receive_buff,sizeof(receive_buff));
		command = receive_buff;
		if(command.compare("hello") == 0)
		{
			cout << "Hello!" << endl;
		}
		else
		{
			cout << command << endl;
		}

		memset(receive_buff,0,sizeof(receive_buff));
	}
}