package com.stonetech.cloud.data;

import java.sql.*;

public class database {

    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/cloud?useSSL=false";

    //  Database credentials
    static final String USER = "root";
    static final String PASS = "19921103";

    private Connection conn;
    private Statement stmt;


    public database(){
        try {
            //加载MYSQL驱动
            Class.forName("com.mysql.jdbc.Driver");
            System.out.println("Connecting to database...");
            //使用默认用户名密码连接数据库
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
            stmt = conn.createStatement();
            if (stmt != null) {
                System.out.println("连接成功！");
            }
            else {
                stmt.close();
                conn.close();
                System.out.println("连接失败！！");
            }
        }catch(Exception e){
            //Handle errors for Class.forName
            e.printStackTrace();
        }
    }

    public int getIDByUsername(String _username){

        if(conn!=null && stmt!=null)
        {
            try {
                String sql;
                sql = "select id from user where username = \"" + _username + "\"";
                ResultSet result = stmt.executeQuery(sql);
                if(result.next()) {
                    int id  = result.getInt("id");
                    if(id == 0){
                        System.out.println("User ID is illegal");
                        return -1;
                    }
                    else {
                        System.out.println("User ID is :" + id);
                        return id;
                    }

                }
                else {
                    System.out.println("Can't get user ID");
                    return -1;
                }
            }catch(SQLException se){
                //Handle errors for JDBC
                se.printStackTrace();
                return -1;
            }catch(Exception e) {
                //Handle errors for Class.forName
                e.printStackTrace();
                return -1;
            }
        }else
            return -1;

    }

    public boolean closeDatabase(){
        try{
            if(stmt!=null){
                stmt.close();
            }
        }catch(SQLException se2){
            se2.printStackTrace();
            return false;
        }
        try{
            if(conn!=null) {
                conn.close();
            }
        }catch(SQLException se){
            se.printStackTrace();
            return false;
        }//end try
        return true;
    }


}
