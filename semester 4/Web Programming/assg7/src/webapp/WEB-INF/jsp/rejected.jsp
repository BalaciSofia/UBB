<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Game Full</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/assets/styles.css">
</head>
<body>
<main class="auth-page">
    <section class="panel auth-panel">
        <h1>Game full</h1>
        <div class="message error">${error}</div>
        <form method="post" action="${pageContext.request.contextPath}/logout">
            <button type="submit">Logout</button>
        </form>
    </section>
</main>
</body>
</html>
