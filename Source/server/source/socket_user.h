#ifndef SOCKET_USER
#define SOCKET_USER



/************************************
*宏定义区
************************************/

//软件版本，通讯协议版本
#define PROTOCOL 1						//通讯协议版本号
#define CLIENTVISION 0x00000001			//当前最新客户端版本号

//客户端运行状态
#define NOTGETVERSION 0					//用户连接到服务器，未发送版本号
#define NOTGETUSERPASS 1				//用户已经发送完版本号，未发送用户名密码

//指令
#define VERSIONCMD 0x01					//版本上传指令
#define USERNAMEPASSCMD 0x02			//用户名密码上传指令

//返回值
#define VERSIONPASS 0x01				//版本验证通过
#define CLIENTVISIONOLD 0x02			//客户端版本过时，可以更新
#define SERVERBUSY 0x81					//服务器繁忙，不可以登陆，稍后重试
#define PROTOCOLINVALID 0x82			//通讯协议版本号无效，可能收到残包，请重发
#define PROTOCOLOLD 0x83				//通讯协议版本号过时，必须更新，不允许登陆
#define CLIENTVISIONINVALID 0x84		//客户端版本无效，可能收到残包，请重发
#define CMDINVALID 0xff					//无效指令，返回值


void* socket_logining_user_thread(void *arg);
void* socket_user_thread(void *arg);

#endif