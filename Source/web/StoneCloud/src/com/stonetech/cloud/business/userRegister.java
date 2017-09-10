package com.stonetech.cloud.business;
import com.stonetech.cloud.data.database;

public class userRegister {

    public userRegister(){

    }

    public boolean checkUsernamExist(String _username){
        database _database = new database();        //创建数据库连接对象
        int _userID = _database.getIDByUsername(_username);//获取此用户名的用户ID
        if(_userID == -1)          //没有此用户名
        {
            _database.closeDatabase();      //关闭数据库连接
            return false;
        }
        else{                       //存在此用户名
            _database.closeDatabase();
            return true;                    //关闭数据库连接
        }

    }

}
