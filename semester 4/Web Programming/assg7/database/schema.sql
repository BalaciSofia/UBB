CREATE DATABASE IF NOT EXISTS assg7;
USE assg7;

CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS players (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    symbol VARCHAR(1) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS game_state (
    id INT PRIMARY KEY,
    board VARCHAR(9) NOT NULL,
    current_turn VARCHAR(1) NOT NULL,
    status VARCHAR(20) NOT NULL,
    winner VARCHAR(1) NULL
);

INSERT IGNORE INTO users(username, password) VALUES
    ('alice', 'pass'),
    ('bob', 'pass'),
    ('carol', 'pass');

INSERT IGNORE INTO game_state(id, board, current_turn, status, winner)
VALUES (1, '---------', 'X', 'WAITING', NULL);
