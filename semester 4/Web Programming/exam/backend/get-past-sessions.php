<?php
session_start();
header('Content-Type: application/json');
require_once 'config.php';

$userID = $_SESSION["userID"];

$statement1 = $conn->prepare(
    "select sessions.*, moves.name AS moveName, moves.difficulty, moves.muscleGroup
     from sessions
     inner join moves on moves.id = sessions.moveID
     where sessions.userID = ?"
);
$statement1->bind_param("i", $userID);
$statement1->execute();
$result = $statement1->get_result();

$sessions = [];

while ($row = $result->fetch_assoc()) {
    $sessions[] = $row;
}

http_response_code(200);

echo json_encode([
    'success' => true,
    'sessions' => $sessions
]);
?>
