#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include "socket_server.h"

using namespace std;




int main(int argc,char* argv[])
{
	pthread_t socket_main_thread_tid;
	int create_thread_err;
	void *rval1;
	
	create_thread_err = pthread_create(&socket_main_thread_tid,NULL,socket_mian_thread,NULL);
	if(create_thread_err != 0)
	{
		cout << "create socket main thread failed! error code: " << create_thread_err << endl;
		return 0;
	}
	
	cout << "socket_server_thread的返回值：" << pthread_join(socket_main_thread_tid,&rval1) << endl;
	cout << "socket_server_thread的退出码是：" <<  (int *)rval1 << endl;
	
	return 0;
	
}