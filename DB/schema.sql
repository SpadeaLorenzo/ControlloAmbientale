CREATE DATABASE controllo_ambientale;

USE controllo_ambientale;

CREATE TABLE user(
    unsername VARCHAR(20) PRIMARY KEY,
    pwd CHAR(255),
);

CREATE TABLE fihsino(
    id INT AUTO_INCREMENT PRIMARY KEY,
    luogo VARCHAR(40),
    nome VARCHAR(20) UNIQUE,
    fishino_username VARCHAR(20),
    FOREIGN KEY fihsino_username REFERENCES fishino(username)
);

CREATE TABLE datas(
    data DATE,
    fihsino_id INT,
    humidity FLOAT,
    brightness FLOAT,
    sound FLOAT,
    temperature FLOAT,
    C02 FOAT,
    FOREIGN KEY fihsino_id REFERENCES fishino(id),
    PRIMARY KEY(data, fihsino_id)
);
