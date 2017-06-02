#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include "socketServer.h"
#include "userDatabase.h"

using namespace std;




int main(int argc,char* argv[])
{
	pthread_t socketServerTid;
	int createThreadErr;
	void *rval1;


	userDatabase userDB;
	try
	{
		string userID = userDB.getUserID("testuser1");
		cout << "userID: " << hex << userID << endl;
	}
	catch(int err)
	{
		cout << err << endl;
	}

	
	createThreadErr = pthread_create(&socketServerTid,NULL,socketServerThread,NULL);
	if(createThreadErr != 0)
	{
		cout << "create socket main thread failed! error code: " << createThreadErr << endl;
		return 0;
	}
	
	cout << "socket_server_thread的返回值：" << pthread_join(socketServerTid,&rval1) << endl;
	cout << "socket_server_thread的退出码是：" <<  (int *)rval1 << endl;
	
	return 0;
	
}