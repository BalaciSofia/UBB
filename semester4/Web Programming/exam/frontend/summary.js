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

        if (score < 40) {
            scoreCell.style.backgroundColor = "red";
        } else if (score < 70) {
            scoreCell.style.backgroundColor = "yellow";
        } else {
            scoreCell.style.backgroundColor = "green";
        }

        row.appendChild(muscleGroupCell);
        row.appendChild(scoreCell);
        scoreMapBody.appendChild(row);
    });
}
