#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <string>
#include <mysql/mysql.h>

using namespace std;

#define SQLSERVER "localhost"
#define SQLUSER "root"
#define SQLPASSWORD "19921103"
#define SQLDATABASE "stonecloud"

class userDatabase
{
public:
	userDatabase();
	~userDatabase();
	bool exeSQL(string sql);

private:
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
};

#endif