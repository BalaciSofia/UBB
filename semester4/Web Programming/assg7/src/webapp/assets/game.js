const root = document.querySelector(".game-page");
const contextPath = root.dataset.contextPath;
const mySymbol = root.dataset.symbol;
const boardElement = document.getElementById("board");
const statusElement = document.getElementById("status");
const feedbackElement = document.getElementById("feedback");
const playersElement = document.getElementById("players");
const resetButton = document.getElementById("reset");
let activeSymbol = mySymbol;

function request(action, body = {}) {
    const params = new URLSearchParams({ action, ...body });
    return fetch(`${contextPath}/game`, {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: params
    }).then(response => {
        if (!response.ok) {
            throw new Error("The server rejected the request.");
        }
        return response.json();
    });
}

function render(state) {
    if (state.redirect) {
        window.location.href = state.redirect;
        return;
    }
    activeSymbol = state.mySymbol || mySymbol;
    boardElement.innerHTML = "";
    [...state.board].forEach((value, index) => {
        const button = document.createElement("button");
        button.type = "button";
        button.className = "cell";
        button.textContent = value === "-" ? "" : value;
        button.disabled = value !== "-" || state.status !== "IN_PROGRESS" || state.currentTurn !== activeSymbol;
        button.addEventListener("click", () => makeMove(index));
        boardElement.appendChild(button);
    });

    playersElement.innerHTML = "";
    state.players.forEach(player => {
        const item = document.createElement("li");
        item.textContent = `${player.username} (${player.symbol})`;
        if (player.symbol === activeSymbol && player.username === state.currentUser) {
            item.className = "current-player";
        }
        playersElement.appendChild(item);
    });

    if (state.players.length < 2) {
        statusElement.textContent = "Waiting for a second player...";
    } else if (state.status === "FINISHED") {
        statusElement.textContent = `Player ${state.winner} won.`;
    } else if (state.status === "DRAW") {
        statusElement.textContent = "Draw. Start a new round.";
    } else {
        statusElement.textContent = state.currentTurn === activeSymbol ? "Your turn." : `Waiting for player ${state.currentTurn}.`;
    }

    let message = state.error || "";
    if (state.mySymbol && state.mySymbol !== mySymbol) {
        message = "This browser tab is using another login session. Open the second player in Incognito or another browser.";
    }
    feedbackElement.classList.toggle("hidden", !message);
    feedbackElement.textContent = message;
}

function refresh() {
    request("state").then(render).catch(showError);
}

function makeMove(cell) {
    request("move", { cell }).then(render).catch(showError);
}

resetButton.addEventListener("click", () => {
    if (confirm("Start a new round?")) {
        request("reset").then(render).catch(showError);
    }
});


function showError(error) {
    feedbackElement.classList.remove("hidden");
    feedbackElement.textContent = error.message;
}

refresh();
setInterval(refresh, 1500);
