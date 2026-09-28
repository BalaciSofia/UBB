<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XO Login</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/assets/styles.css">
</head>
<body>
<main class="auth-page">
    <section class="panel auth-panel">
        <h1>XO Game</h1>
        <p class="muted">Sign in to enter the two-player room.</p>

        <% if (request.getAttribute("error") != null) { %>
        <div class="message error"><%= request.getAttribute("error") %></div>
        <% } %>

        <form method="post" action="${pageContext.request.contextPath}/login" class="form">
            <label>
                Username
                <input name="username" type="text" minlength="3" pattern="[A-Za-z0-9_]+"
                       required autocomplete="username">
            </label>
            <label>
                Password
                <input name="password" type="password" minlength="3" required
                       autocomplete="current-password">
            </label>
            <button type="submit">Login</button>
        </form>
    </section>
</main>
</body>
</html>
