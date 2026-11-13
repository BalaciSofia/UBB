

let currentMove = null;
const scoreMapBody = document.getElementById("score-map");
renderScoreMap(JSON.parse(sessionStorage.getItem("muscleGroupScores") || "{}"));

function renderScoreMap(scoreMap) {
    scoreMapBody.innerHTML = "";

    Object.entries(scoreMap).forEach(([muscleGroup, score]) => {
        const row = document.createElement("tr");
        const muscleGroupCell = document.createElement("td");
        const scoreCell = document.createElement("td");

        muscleGroupCell.textContent = muscleGroup;
        scoreCell.textContent = score;

        row.appendChild(muscleGroupCell);
        row.appendChild(scoreCell);
        scoreMapBody.appendChild(row);
    });
}

async function loadNextMove() {
    const response = await fetch("/exam/backend/get-next-move.php");
    const data = await response.json();

    if (!data.success) {
        currentMove = null;
        moveBox.textContent = data.message;
        return;
    }

    currentMove = data.move;
    moveBox.textContent = `${currentMove.name},${currentMove.muscleGroup},difficulty ${currentMove.difficulty}`;
}
loadNextMove();

const moveBox = document.getElementById("move");
const moveForm = document.getElementById("move-form");
moveForm.addEventListener("submit", submitMove);

async function submitMove(event) {
    event.preventDefault();

    const completed = moveForm.completed.value;
    const scoreMap = JSON.parse(sessionStorage.getItem("muscleGroupScores") || "{}");
    const oldScore = Number(scoreMap[currentMove.muscleGroup]);

    if (completed === "1") {
        scoreMap[currentMove.muscleGroup] = Math.min(100, oldScore + 10);
    } else {
        scoreMap[currentMove.muscleGroup] = Math.round(oldScore - oldScore * 0.8);
    }

    await fetch("/exam/backend/submit-move.php", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            moveID: currentMove.id,
            completed: completed,
            muscleGroupScores: scoreMap
        })
    });

    sessionStorage.setItem("muscleGroupScores", JSON.stringify(scoreMap));
    renderScoreMap(scoreMap);
    moveForm.reset();
    loadPastSessions();
    loadNextMove();
}

async function loadPastSessions() {
    const response = await fetch("/exam/backend/get-past-sessions.php");
    const data = await response.json();
    const sessionsLog = document.getElementById("sessions-log");

    sessionsLog.innerHTML = "";

    data.sessions.forEach((session) => {
        const row = document.createElement("tr");
        const moveCell = document.createElement("td");
        const muscleGroupCell = document.createElement("td");
        const difficultyCell = document.createElement("td");
        const completedCell = document.createElement("td");

        moveCell.textContent = session.moveName;
        muscleGroupCell.textContent = session.muscleGroup;
        difficultyCell.textContent = session.difficulty;
        completedCell.textContent = session.completed;

        row.appendChild(moveCell);
        row.appendChild(muscleGroupCell);
        row.appendChild(difficultyCell);
        row.appendChild(completedCell);
        sessionsLog.appendChild(row);
    });
}
loadPastSessions();
