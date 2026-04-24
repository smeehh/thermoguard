# ThermoGuard

Projet BTS CIEL – Système de surveillance thermique ESP32 + Raspberry Pi

##  Description

ThermoGuard est un système IoT permettant de surveiller la température et l’humidité en temps réel.

En cas de dépassement de seuil :
- envoi d’un email
- activation LED + buzzer
- affichage sur dashboard web
- enregistrement en base de données

##  Technologies utilisées

- ESP32 + DHT22
- MQTT sécurisé (TLS)
- Node-RED
- Raspberry Pi
- MariaDB
- Dashboard web
- HTTPS

##  Sécurité

- MQTT chiffré (TLS)
- authentification utilisateur
- accès dashboard sécurisé (HTTPS)

##  Fonctionnement

1. L’ESP32 envoie les données
2. Node-RED traite les valeurs
3. Si seuil dépassé :
   - alerte envoyée
   - LED + buzzer activés
4. Données stockées en base
