# Installation et vérification du broker MQTT Mosquitto

## 1. Contexte

Dans le cadre du projet BTS CIEL – Système de surveillance thermique, le Raspberry Pi joue le rôle de serveur central.
Il héberge le broker MQTT Mosquitto, chargé de recevoir et redistribuer les messages envoyés par l’ESP32.

---

## 2. Installation de Mosquitto

Mise à jour du système :

sudo apt update
sudo apt upgrade -y

Installation du broker MQTT et des outils clients :

sudo apt install mosquitto mosquitto-clients -y

---

## 3. Vérification du service Mosquitto

Vérification que le service est actif :

sudo systemctl status mosquitto

Résultat attendu :
Active: active (running)

Vérification du démarrage automatique au boot :

sudo systemctl is-enabled mosquitto

Résultat attendu :
enabled

Cela signifie que Mosquitto démarre automatiquement au démarrage du Raspberry Pi.

---

## 4. Test local publish / subscribe

Test de fonctionnement du broker en local.

Fenêtre 1 (abonnement) :
mosquitto_sub -t test

Fenêtre 2 (publication) :
mosquitto_pub -t test -m "Test BTS CIEL"

Si le message apparaît dans la première fenêtre, le broker fonctionne correctement.

---

## 5. Conclusion

Le broker MQTT Mosquitto est :

- installé correctement
- actif en tant que service systemd
- configuré pour démarrer automatiquement
- fonctionnel (test publish/subscribe validé)

Le serveur est donc prêt à recevoir les données provenant de l’ESP32.
