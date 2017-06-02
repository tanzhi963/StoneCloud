#include <iostream>
#include <unistd.h>
#include <string>
#include <string.h>

#include "user.h"
#include "login.h"

using namespace std;

#define RECEIVE_LENGTH 1024
#define RETURN_LENGTH 1024



void* login(void *arg)
{
	user *newUser = (user *)arg;			//将对象转换回来
	bool _connectStatus = 1;											//用来表示用户当前SOCKET连接状态，连接：1；断开：0
	char _receiveData[RECEIVE_LENGTH] = {0};							//存放客户端发送来的指令信息
	char _returnBuff[RETURN_LENGTH] = {0};								//存放返回客户端的指令
	while(_connectStatus)												//一直接收指令
	{
		//读取从客户端发送来的指令
		int _readLengthCount = read(newUser->getSocketid(),_receiveData,sizeof(_receiveData));
		//当前客户端尚未上传通讯协议版本号
		if(newUser->getStatus() == NOTGETVERSION)
		{
			if(_receiveData[0] == VERSIONCMD)							//如果收到是版本指令
			{
				if(_receiveData[1] < PROTOCOL)							//客户端通讯协议的版本号是旧版本
				{
					newUser->returnChar(PROTOCOLOLD);			//有新版通讯协议更新，必须更新客户端，不允许登录
				}
				else if(_receiveData[1] == PROTOCOL)					//是最新的通讯协议
				{
					unsigned int _clientVersion = 0;						//获取客户端版本号
					for(int i=2;i<6;i++)
					{
						_clientVersion |= (unsigned int)_receiveData[i] << ((5-i)*8);
					}
					if(_clientVersion <= CLIENTVISION)					//客户端版本号合法
					{
						newUser->setProtocol(_receiveData[1]);			//赋值通讯协议版本号
						newUser->setClientVersion(_clientVersion);		//赋值客户端版本号
						newUser->setStatus(NOTGETUSERPASS);				//设置状态为未上传用户名密码
						if(_clientVersion == CLIENTVISION)
						{
							newUser->returnChar(VERSIONPASS);	//版本为最新，返回正常
						}
						else
						{
							newUser->returnChar(CLIENTVISIONOLD);	//客户端版本较低，提示升级，可以下一步
						}
					}
					else												//客户端版本号异常，请重新发送
					{
						newUser->returnChar(CLIENTVISIONINVALID);
					}
					
				}
				else													//收到错误版本号，可能收到残包
				{
					newUser->returnChar(PROTOCOLINVALID);		//版本号未知，可能收到残包，请重新发送
				}
			}
			else														//收到其他指令
			{
				newUser->returnChar(CMDINVALID);				//返回错误“-1”
			}
		}
		//已经上传协议版本号，等待上传用户名和密码
		else if(newUser->getStatus() == NOTGETUSERPASS)
		{
			if(_receiveData[0] == USERNAMEPASSCMD)						//收到用户名密码指令
			{
				//收到用户名密码登陆指令，将用户名和密码赋值到缓存中进行保存，并进行检查
				char _userNameLength = _receiveData[1];
				char _userPassLength = _readLengthCount-_userNameLength-2;
				char _userName[_userNameLength] = {0};
				char _userPass[_userPassLength] = {0};
				strncpy(_userName,_receiveData+2,_userNameLength);
				strncpy(_userPass,_receiveData+_userNameLength+2,_userPassLength);
				string _userNameStr = _userName;
				string _userPassStr = _userPass;
				//检查用户名密码是否正确
				int checkUserNamePasswordResult = newUser->checkUserNamePassword(_userNameStr,_userPassStr);
				if(checkUserNamePasswordResult == 0)							//用户名密码检测通过
				{
					_returnBuff[0] = 0x01;
					newUser->setStatus(NOTGETVERSION);
					int wirteErr = write(newUser->getSocketid(),_returnBuff,1);
				}
				else if(checkUserNamePasswordResult == 1)						//密码不匹配
				{
					_returnBuff[0] = 0xf0;
					int wirteErr = write(newUser->getSocketid(),_returnBuff,1);
				}
				else if(checkUserNamePasswordResult == 2)						//没有此用户名
				{
					_returnBuff[0] = 0xf1;
					int wirteErr = write(newUser->getSocketid(),_returnBuff,1);
				}
			}
			else
			{
				_returnBuff[0] = 0xff;
				int wirteErr = write(newUser->getSocketid(),_returnBuff,1);
			}
		}
		else
		{

		}
		

		memset(_receiveData,0,sizeof(_receiveData));
		memset(_returnBuff,0,sizeof(_returnBuff));
	}
}

