<?php
session_start();
header('Content-Type: application/json');
require_once 'config.php';

$data = json_decode(file_get_contents("php://input"), true);
$userID = $_SESSION["userID"];
$moveID = $data["moveID"];
$completed = $data["completed"];
$muscleGroupScores = $data["muscleGroupScores"];

$statement = $conn->prepare("insert into sessions (userID, moveID, completed) values (?, ?, ?)");
$statement->bind_param("iii", $userID, $moveID, $completed);
$statement->execute();

$_SESSION["muscleGroupScores"] = $muscleGroupScores;

echo json_encode([
    "success" => true,
    "muscleGroupScores" => $muscleGroupScores
]);
?>
