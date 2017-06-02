#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "socketServer.h"
#include "login.h"
#include "user.h"

using namespace std;


void* socketServerThread(void *arg)
{
	cout << "socket mian thread created success!" << endl;
	//创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = INADDR_ANY;  //具体的IP地址
    serv_addr.sin_port = htons(60000);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);
    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int client_count = 0;
	
	while(1)
	{
		//等待用户发起请求
		int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        pthread_t _tid = 0;
		user *newUser = new user();			
        newUser->setSocketid(clnt_sock);

        int createThreadErr = pthread_create(&_tid,NULL,login,(void*)newUser);
        if(createThreadErr != 0)
        {
            cout << "create socket user thread failed! error code: " << createThreadErr << endl;
        }
        else
        {
            newUser->setTid(_tid);
        }

		
	}
   
    //关闭套接字
    close(serv_sock);
	
	return (void*)1;
}




