<%--
  Created by IntelliJ IDEA.
  User: STUDENT
  Date: 2020-11-30
  Time: 13:19
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <title>Check Mathematical Expression</title>
</head>
<body>

<form action="${pageContext.request.contextPath}/input" method="POST">
    Invalid characters are prefixed with $, lacking brackets are marked with '#', '`', '@', '|'
    Type in mathematical expression(don't use #,$,@,`):
    <label>
        <input type="text" name="inputText" value="">
    </label>
    <input type="submit" name="button" value="CHECK">
</form>
<form action="${pageContext.request.contextPath}/previousInput" method="POST">
    Click to see previous expressions:
    <input type="submit" name="button2" value="SEE">
</form>

</body>
</html>
