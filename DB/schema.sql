CREATE DATABASE controllo_ambientale;

use controllo_ambientale;

--finshino's data--
CREATE TABlE fishino(
    id INT AUTO_INCREMEN PRIMARY KEY,
    MAC_address VARCHAR(20) UNIQUE,
    luogo VARCHAR(30)
);

--brightness sensor data--
CREATE TABLE luce(
    dato VARCHAR(10),
    DATETIME cur_time,
    fishino_id INT,
    FOREIGN KEY(fishino_id) REFERENCES fishino(id),
    PRIMARY KEY(cur_time,fishino_id)
);

--umidity sensor data--
CREATE TABLE umidita(
    dato varchar(10),
    DATETIME cur_time,
    fishino_id INT,
    FOREIGN KEY(fishino_id) REFERENCES fishino(id),
    PRIMARY KEY(cur_time,fishino_id)
);

--sound sensor data--
CREATE TABLE souno(
    dato varchar(10),
    DATETIME cur_time,
    fishino_id INT,
    FOREIGN KEY(fishino_id) REFERENCES fishino(id),
    PRIMARY KEY(cur_time,fishino_id)
);

--air sensor data--
CREATE TABLE CO2(
    dato varchar(10),
    DATETIME cur_time,
    fishino_id INT,
    FOREIGN KEY(fishino_id) REFERENCES fishino(id),
    PRIMARY KEY(cur_time,fishino_id)
);