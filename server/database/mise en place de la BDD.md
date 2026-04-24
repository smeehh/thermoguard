#  Mise en place de la base de données ThermoGuard

##  Objectif

L’objectif de la base de données est de stocker les mesures de température et d’humidité envoyées par l’ESP32 afin de :

* conserver un **historique des données**
* permettre une **analyse des variations**
* alimenter le **dashboard en temps réel**
* tracer les événements (conditions normales / alertes)

---

##  Installation de MariaDB

Sur le Raspberry Pi :

```bash
sudo apt update
sudo apt install mariadb-server
```

Vérification du service :

```bash
sudo systemctl status mariadb
```

---

##  Sécurisation de MariaDB

```bash
sudo mysql_secure_installation
```

Options recommandées :

* définir un mot de passe root
* supprimer les utilisateurs anonymes
* désactiver l’accès root à distance
* supprimer la base de test

---

##  Création de la base de données

Connexion à MariaDB :

```bash
mysql -u root -p
```

---

##  Création de la base et de la table

```sql
CREATE DATABASE thermoguard;

USE thermoguard;

CREATE TABLE mesures (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperature FLOAT,
  humidite FLOAT,
  date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

---

##  Structure de la table

| Champ       | Type      | Description               |
| ----------- | --------- | ------------------------- |
| id          | INT       | Identifiant unique        |
| temperature | FLOAT     | Température mesurée (°C)  |
| humidite    | FLOAT     | Humidité mesurée (%)      |
| date        | TIMESTAMP | Date et heure automatique |

---

##  Intégration avec Node-RED

Le flux Node-RED permet :

1. de recevoir les données MQTT
2. de traiter les valeurs
3. d’insérer les données dans la base

### Exemple de requête SQL utilisée :

```sql
INSERT INTO mesures (temperature, humidite)
VALUES ({{temperature}}, {{humidite}});
```

---

##  Vérification des données

Dans MariaDB :

```sql
SELECT * FROM mesures ORDER BY id DESC LIMIT 10;
```

---

##  Exploitation des données

Les données stockées permettent :

* l’affichage de l’historique sur le dashboard
* la visualisation de l’évolution (graphiques)
* la détection d’anomalies
* l’analyse des conditions environnementales

---

##  Résultat

* stockage fiable des mesures
* historisation automatique
* intégration avec Node-RED
* visualisation en temps réel

---

##  Conclusion

La base de données joue un rôle essentiel dans le projet ThermoGuard.
Elle permet de conserver les données dans le temps, d’analyser les tendances et d’améliorer la prise de décision en cas d’alerte.

Ce système transforme un simple capteur en une solution de surveillance complète et exploitable.
