CREATE DATABASE thermoguard;

USE thermoguard;

CREATE TABLE mesures (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperature FLOAT,
  humidite FLOAT,
  date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
