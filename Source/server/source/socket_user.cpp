#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>

#include "socket_user.h"
#include "logining_user.h"
#include "user.h"

using namespace std;

#define RECEIVE_LENGTH 1024
#define RETURNLENGTH 1024



void* socket_logining_user_thread(void *arg)
{
	logining_user *logining_user_new = (logining_user *)arg;			//将对象转换回来
	bool connect_status = 1;											//用来表示用户当前SOCKET连接状态，连接：1；断开：0
	char receive_buff[RECEIVE_LENGTH] = {0};							//存放客户端发送来的指令信息
	char returnBuff[RETURNLENGTH] = {0};								//存放返回客户端的指令
	while(connect_status)												//一直接收指令
	{
		//读取从客户端发送来的指令
		int read_length_count = read(logining_user_new->get_socketid(),receive_buff,sizeof(receive_buff));
		//当前客户端尚未上传通讯协议版本号
		if(logining_user_new->get_status() == NOTGETVERSION)
		{
			if(receive_buff[0] == VERSIONCMD)							//如果收到是版本指令
			{
				if(receive_buff[1] < PROTOCOL)							//客户端通讯协议的版本号是旧版本
				{
					logining_user_new->returnChar(PROTOCOLOLD);			//有新版通讯协议更新，必须更新客户端，不允许登录
				}
				else if(receive_buff[1] == PROTOCOL)					//是最新的通讯协议
				{
					unsigned int clientVersion = 0;						//获取客户端版本号
					for(int i=2;i<6;i++)
					{
						clientVersion |= (unsigned int)receive_buff[i] << ((5-i)*8);
					}
					if(clientVersion <= CLIENTVISION)					//客户端版本号合法
					{
						logining_user_new->set_protocol(receive_buff[1]);			//赋值通讯协议版本号
						logining_user_new->set_clientVersion(clientVersion);		//赋值客户端版本号
						logining_user_new->set_status(NOTGETUSERPASS);				//设置状态为未上传用户名密码
						if(clientVersion == CLIENTVISION)
						{
							logining_user_new->returnChar(VERSIONPASS);	//版本为最新，返回正常
						}
						else
						{
							logining_user_new->returnChar(CLIENTVISIONOLD);	//客户端版本较低，提示升级，可以下一步
						}
					}
					else												//客户端版本号异常，请重新发送
					{
						logining_user_new->returnChar(CLIENTVISIONINVALID);
					}
					
				}
				else													//收到错误版本号，可能收到残包
				{
					logining_user_new->returnChar(PROTOCOLINVALID);		//版本号未知，可能收到残包，请重新发送
				}
			}
			else														//收到其他指令
			{
				logining_user_new->returnChar(CMDINVALID);				//返回错误“-1”
			}
		}
		//已经上传协议版本号，等待上传用户名和密码
		else if(logining_user_new->get_status() == NOTGETUSERPASS)
		{
			if(receive_buff[0] == USERNAMEPASSCMD)						//收到用户名密码指令
			{
				//收到用户名密码登陆指令，将用户名和密码赋值到缓存中进行保存，并进行检查
				char user_name_length = receive_buff[1];
				char user_pass_length = read_length_count-user_name_length-2;
				char user_name_buff[user_name_length] = {0};
				char user_pass_buff[user_pass_length] = {0};
				for(int i=0;i<user_name_length;i++)
				{
					user_name_buff[i] = receive_buff[i+2];
				}
				for(int i=0;i<user_pass_length;i++)
				{
					user_pass_buff[i] = receive_buff[i+user_name_length+2];
				}
				//检查用户名密码是否正确
				int checkUserNamePasswordResult = logining_user_new->checkUserNamePassword(user_name_buff,user_pass_buff);
				if(checkUserNamePasswordResult == 0)							//用户名密码检测通过
				{
					returnBuff[0] = 0x01;
					logining_user_new->set_status(NOTGETVERSION);
					int wirteErr = write(logining_user_new->get_socketid(),returnBuff,1);
				}
				else if(checkUserNamePasswordResult == 1)						//密码不匹配
				{
					returnBuff[0] = 0xf0;
					int wirteErr = write(logining_user_new->get_socketid(),returnBuff,1);
				}
				else if(checkUserNamePasswordResult == 2)						//没有此用户名
				{
					returnBuff[0] = 0xf1;
					int wirteErr = write(logining_user_new->get_socketid(),returnBuff,1);
				}
			}
			else
			{
				returnBuff[0] = 0xff;
				int wirteErr = write(logining_user_new->get_socketid(),returnBuff,1);
			}
		}
		else
		{

		}
		

		memset(receive_buff,0,sizeof(receive_buff));
		memset(returnBuff,0,sizeof(returnBuff));
	}
}

void* socket_user_thread(void *arg)
{
	
}

