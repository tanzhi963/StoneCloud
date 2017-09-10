<%--
  Created by IntelliJ IDEA.
  User: Leon
  Date: 2017/9/6 0006
  Time: 22:46
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="com.stonetech.cloud.business.userRegister" %>
<html>
  <head>
    <title>$Title$</title>
  </head>
  <body>
  <h1>Hello World</h1>
  <%
    userRegister _userRegister = new userRegister();
    boolean _result = _userRegister.checkUsernamExist("tanzhi9631");
    out.println("User ID is:"+_result);
  %>
  </body>
</html>
