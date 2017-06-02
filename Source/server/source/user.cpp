#include <iostream>
#include <unistd.h>
#include "user.h"
#include "login.h"

using namespace std;

user::user()
{
	cout << "user object created !" << endl;
	this -> setStatus(NOTGETVERSION);
}

user::~user()
{
	cout << "user object be free !" << endl;
}

char user::checkUserNamePassword(string _name,string _password)
{

}

char user::returnChar(unsigned char _data)
{
	unsigned char returnBuff[1] ={_data};
	char wirteErr = write(this->getSocketid(),returnBuff,1);
	return wirteErr;
}

void user::setSocketid(int _iSocketid)
{
	m_iSocketid = _iSocketid;
}

int user::getSocketid()
{
	return m_iSocketid;
}

void user::setTid(pthread_t _tid)
{
	m_pTid = _tid;
}

int user::getTid()
{
	return m_pTid;
}

void user::setStatus(int _status)
{
	m_iStatus = _status;
}

int user::getStatus()
{
	return m_iStatus;
}

void user::setProtocol(char _protocol)
{
	m_cProtocol = _protocol;
}

char user::getProtocol()
{
	return m_cProtocol;
}

void user::setClientVersion(unsigned int _clientVersion)
{
	m_iClientVersion = _clientVersion;
}

unsigned int user::getClientVersion()
{
	return m_iClientVersion;
}

