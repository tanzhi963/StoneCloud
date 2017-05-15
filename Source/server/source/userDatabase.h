#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <string>
#include <mysql/mysql.h>

class userDatabase
{
public:
	userDatabase();
	~userDatabase();

private:
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
};

#endif