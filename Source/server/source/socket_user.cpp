#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>

#include "socket_user.h"
#include "logining_user.h"
#include "user.h"

using namespace std;

#define RECEIVE_LENGTH 1024


string command_tables[] = {
	"hello",
	"bye"
};


void* socket_logining_user_thread(void *arg)
{
	logining_user *logining_user_new = (logining_user *)arg;				//将对象转换回来
	bool connect_status = 1;					//用来表示用户当前SOCKET连接状态，连接：1；断开：0
	char receive_buff[RECEIVE_LENGTH] = {0};	//存放客户端发送来的指令信息
	while(connect_status)						//一直接收指令
	{
		//读取从客户端发送来的指令
		int read_length_count = read(logining_user_new->get_socketid(),receive_buff,sizeof(receive_buff));
		//当前客户端尚未上传通讯协议版本号
		if(logining_user_new->get_status() == NOTGETVERSION)
		{
			if(strncmp("v",receive_buff,1) == 0)
			{
				logining_user_new->set_protocol(receive_buff[1]);
				logining_user_new->set_status(NOTGETUSERPASS);
			}
		}
		//已经上传协议版本号，等待上传用户名和密码
		else if(logining_user_new->get_status() == NOTGETUSERPASS)
		{
			if(strncmp("l",receive_buff,1) == 0)
			{

			}
		}
		

		memset(receive_buff,0,sizeof(receive_buff));
	}
}

void* socket_user_thread(void *arg)
{
	
}

int command_analysis(char *command)
{
	int i;
	string command_str = command;
	int command_tables_length = sizeof(command_tables) / sizeof(command_tables[0]);
	cout << "buff length is :" << command_tables_length << endl;
	for(i=0;i<=command_tables_length-1;i++)
	{
		if(command_str == command_tables[i])
		{
			return i;
		}
	}
	return -1;	
}