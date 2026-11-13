<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!doctype html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>

    <% if (request.getAttribute("error") != null) { %>
    <p style="color:#e34343"><%= request.getAttribute("error") %></p>
    <% } %>

    <form method="post" action="${pageContext.request.contextPath}/login">
        <input type="text" name="username" placeholder="Username" required>
        <button type="submit">Login</button>
    </form>
</body>
</html>