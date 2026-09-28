<?php
session_start();
header('Content-Type: application/json');
require_once 'config.php';

$data = json_decode(file_get_contents("php://input"), true);
$username = $data['username'] ?? '';

$statement = $conn->prepare("SELECT * FROM users WHERE username = ?");
$statement->bind_param("s", $username);
$statement->execute();

$result = $statement->get_result();
$user = $result->fetch_assoc();

if (!$user) {
    http_response_code(401);
    echo json_encode(['success' => false, 'message' => 'Invalid username']);
    exit;
}

$userID = (int)$user['id'];

$statement1 = $conn->prepare(
    "select sessions.*, moves.name AS moveName, moves.difficulty, moves.muscleGroup
     from sessions
     inner join moves on moves.id = sessions.moveID
     where sessions.userID = ?
     order by sessions.id"
);
$statement1->bind_param("i", $userID);
$statement1->execute();
$result = $statement1->get_result();

$sessions = [];
$muscleGroupScores = [];

$groupsResult = $conn->query("select distinct muscleGroup from moves");
while ($group = $groupsResult->fetch_assoc()) {
    $muscleGroupScores[$group['muscleGroup']] = 0;
}

while ($row = $result->fetch_assoc()) {
    $sessions[] = $row;

    $muscleGroup = $row['muscleGroup'];
    $completed = (int)$row['completed'];

    if ($completed === 1) {
        $muscleGroupScores[$muscleGroup] = min(100, $muscleGroupScores[$muscleGroup] + 10);
    } else {
        $muscleGroupScores[$muscleGroup] = (int)round($muscleGroupScores[$muscleGroup] - $muscleGroupScores[$muscleGroup] * 0.8);
    }
}

$_SESSION['userID'] = $userID;
$_SESSION['muscleGroupScores'] = $muscleGroupScores;

$redirect = "/exam/frontend/home.html";

http_response_code(200);

echo json_encode([
    'success' => true,
    'message' => 'Login successful',
    'redirect' => $redirect,
    'sessions' => $sessions,
    'muscleGroupScores' => $muscleGroupScores
]);
?>
