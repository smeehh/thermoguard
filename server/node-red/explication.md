#  Fonctionnement du flux Node-RED (ThermoGuard)

##  Objectif

Le flux Node-RED permet de traiter les données envoyées par l’ESP32 via MQTT afin de :

* afficher les mesures en temps réel
* stocker les données dans une base
* déclencher des alertes en cas de dépassement de seuil
* piloter des actions (LED, buzzer)

---

##  Réception des données

Deux topics MQTT sont utilisés :

```text
thermoguard/temperature
thermoguard/humidite
```

 Node-RED reçoit ces données via des nodes **MQTT IN**

---

##  Traitement et affichage

Les données reçues sont envoyées vers plusieurs composants :

* **jauge (gauge)** → affichage instantané de la température
* **graphique (chart)** → évolution dans le temps
* **texte (text)** → affichage de la valeur actuelle

 Cela permet une visualisation claire sur le dashboard web

---

##  Détection d’alerte

Un node **switch** est utilisé pour analyser la température :

* si `température > 30°C` → condition d’alerte
* si `température ≤ 30°C` → état normal

---

##  Gestion des alertes

###  Cas critique (température > 30°C)

Plusieurs actions sont déclenchées :

1. **Envoi d’un email**

   * notification automatique
   * message contenant la température

2. **Commande MQTT**

   * envoi du message `"ON"` sur :

   ```text
   thermoguard/alerte
   ```

   * activation de la LED et du buzzer sur l’ESP32

---

###  Retour à la normale (température ≤ 30°C)

* envoi du message `"OFF"` sur :

```text
thermoguard/alerte
```

 désactivation de la LED et du buzzer

---

##  Enregistrement en base de données

Les données sont combinées (température + humidité) via un node **join**.

Puis une requête SQL est exécutée :

```sql
INSERT INTO mesures (temperature, humidite)
VALUES (temp, hum);
```

 Cela permet de stocker l’historique des mesures

---

##  Historique

Les données enregistrées sont utilisées pour :

* afficher un historique sur le dashboard
* analyser l’évolution des conditions

---

##  Schéma simplifié du flux

```text
ESP32
  ↓
MQTT (température / humidité)
  ↓
Node-RED
  ├── Dashboard (jauge, graphique)
  ├── Switch (>30°C)
  │     ├── Email
  │     ├── MQTT ON (alerte)
  │     └── MQTT OFF (normal)
  └── Base de données (historique)
```

---

##  Résultat

Grâce à ce flux Node-RED :

* les données sont traitées en temps réel
* les alertes sont automatiques
* les actions physiques sont déclenchées
* les mesures sont stockées et exploitables

---

##  Conclusion

Node-RED joue un rôle central dans le projet ThermoGuard.

Il agit comme un **système de décision intelligent**, capable de :

* analyser les données
* déclencher des actions
* centraliser les informations

Cela permet de transformer un simple capteur en un système de surveillance complet et automatisé.
