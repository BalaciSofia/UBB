<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XO Game</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/assets/styles.css">
</head>
<body>
<main class="game-page" data-context-path="${pageContext.request.contextPath}" data-symbol="${symbol}">
    <header class="topbar">
        <div>
            <h1>XO Game</h1>
            <p class="muted">Logged in as <strong>${sessionScope.username}</strong>, playing <strong>${symbol}</strong>.</p>
        </div>
        <form method="post" action="${pageContext.request.contextPath}/logout" onsubmit="return confirm('Leave the game?');">
            <button type="submit" class="secondary">Logout</button>
        </form>
    </header>

    <section class="game-layout">
        <div class="board-wrap">
            <div id="status" class="message">Loading game...</div>
            <div id="board" class="board" aria-label="XO board"></div>
            <div id="feedback" class="message error hidden"></div>
            <button id="reset" class="secondary" type="button">New round</button>
        </div>

        <aside class="panel players-panel">
            <h2>Players</h2>
            <ul id="players" class="players"></ul>
        </aside>
    </section>
</main>

<script src="${pageContext.request.contextPath}/assets/game.js"></script>
</body>
</html>
