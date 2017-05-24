#include <iostream>
#include "userDatabase.h"

using namespace std;

userDatabase::userDatabase()
{
	connection = mysql_init(NULL);			// 初始化数据库连接变量
	if(connection == NULL)				//初始化函数执行失败
	{
		cout << "mysql init error:" << mysql_error(connection) << endl;
		throw 0x01;							//如果初始化异常，则抛出0x01作为异常
	}
	else									//初始化执行成功
	{
		//函数mysql_real_connect建立一个数据库连接
		//成功返回MYSQL*连接句柄，失败返回NULL
		connection = mysql_real_connect(connection, SQLSERVER, SQLUSER, SQLPASSWORD, SQLDATABASE, 0, NULL, 0);
		if(connection == NULL)
		{
			cout << "mysql real connect error:" << mysql_error(connection) << endl;
			throw 0x02;						//连接异常，抛出0x02异常
		}
	}

}

userDatabase::~userDatabase()
{
	if(connection != NULL)// 关闭数据库连接
	{
		mysql_close(connection);
	}
}


bool userDatabase::exeSQL(string sql)
{
	// mysql_query()执行成功返回0，失败返回非0值。与PHP中不一样
	if(mysql_query(connection, sql.c_str()))
	{
		cout << "mysql query error:" << mysql_error(connection) << endl; 
		return false;
	}
	else
	{
		result = mysql_use_result(connection); // 获取结果集
		// mysql_field_count()返回connection查询的列数
		for(int i=0; i < mysql_field_count(connection); i++)
		{
			// 获取下一行
			row = mysql_fetch_row(result);
			if(row <= 0)
			{
				break;
			}
			// mysql_num_fields()返回结果集中的字段数
			for(int j=0; j < mysql_num_fields(result); j++)
			{
				cout << row[j] << " " ;
			}
			cout << endl;
		}
		cout << "mysql_field_count : " << mysql_field_count(connection) << endl;
		cout << "mysql_num_fields : " << mysql_num_fields(result) << endl;

		// 释放结果集的内存
		mysql_free_result(result);
	}
	return true;
}

int userDatabase::getUserID(string _userName)
{
	string _sqlQuery = "select id from user where username = '" + _userName + "'";
	if(mysql_query(connection, _sqlQuery.c_str()))
	{
		cout << "mysql query error:" << mysql_error(connection) << endl; 
		return false;
	}
	result = mysql_use_result(connection); // 获取结果集
	if(mysql_field_count(connection) < 1)
	{
		
	}
}
