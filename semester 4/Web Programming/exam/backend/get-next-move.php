<?php
session_start();
header('Content-Type: application/json');
require_once 'config.php';

$userID = $_SESSION["userID"];
$muscleGroupScores = $_SESSION["muscleGroupScores"];

asort($muscleGroupScores);

foreach ($muscleGroupScores as $muscleGroup => $score) {
    if ($score < 40) {
        $difficulty = 1;
    } else if ($score < 70) {
        $difficulty = 2;
    } else {
        $difficulty = 3;
    }

    $statement = $conn->prepare(
        "select * from moves where muscleGroup = ? and difficulty = ? and id not in
        (select moveID from sessions where userID = ?)
        limit 1"
    );
    $statement->bind_param("sii", $muscleGroup, $difficulty, $userID);
    $statement->execute();

    $result = $statement->get_result();
    $move = $result->fetch_assoc();

    if ($move !== null) {
        http_response_code(200);
        echo json_encode([
            'success' => true,
            'move' => $move
        ]);
        exit;
    }
}

http_response_code(200);
echo json_encode([
    'success' => false,
    'message' => 'No move available'
]);
?>
