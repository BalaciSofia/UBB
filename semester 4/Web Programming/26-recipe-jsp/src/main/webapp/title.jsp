<%--
  Created by IntelliJ IDEA.
  User: balac
  Date: 6/14/2026
  Time: 6:37 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Start</title>
</head>
<body>
<h2>Name your recipe</h2>

<form method="post" action="${pageContext.request.contextPath}/title">
    <input type="text" name="title" placeholder="title" required>
    <button type="submit">Next</button>
</form>

</body>
</html>
