#  Sécurisation MQTT avec TLS (Mosquitto)

##  Objectif

L’objectif est de sécuriser les communications entre l’ESP32 et le serveur MQTT (Mosquitto) afin de garantir :

* la **confidentialité** des données (chiffrement)
* l’**authentification** des clients
* l’**intégrité** des messages échangés

Sans sécurisation, les données transitent en clair et peuvent être interceptées.

---

##  Installation du broker MQTT

Sur le Raspberry Pi :

```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients
```

---

##  Mise en place du chiffrement TLS

### 1. Création du dossier des certificats

```bash
sudo mkdir /etc/mosquitto/certs
cd /etc/mosquitto/certs
```

---

### 2. Génération de l’autorité de certification (CA)

```bash
openssl req -new -x509 -days 365 -nodes -out ca.crt -keyout ca.key
```

 Cette autorité servira à signer les certificats du serveur.

---

### 3. Génération du certificat serveur

```bash
openssl req -new -nodes -out server.csr -keyout server.key
```

Puis signature :

```bash
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 365
```

---

##  Configuration de Mosquitto

Créer ou modifier le fichier :

```bash
sudo nano /etc/mosquitto/conf.d/tls.conf
```

Contenu :

```conf
listener 8883
cafile /etc/mosquitto/certs/ca.crt
certfile /etc/mosquitto/certs/server.crt
keyfile /etc/mosquitto/certs/server.key

allow_anonymous false
password_file /etc/mosquitto/passwd
```

---

##  Création d’un utilisateur MQTT

```bash
sudo mosquitto_passwd -c /etc/mosquitto/passwd semih
```

 Un mot de passe est demandé pour sécuriser l’accès.

---

##  Redémarrage du service

```bash
sudo systemctl restart mosquitto
```

---

##  Connexion sécurisée côté ESP32

L’ESP32 utilise :

* `WiFiClientSecure`
* le certificat `ca.crt`
* le port sécurisé **8883**

Exemple :

```cpp
WiFiClientSecure espClient;
espClient.setCACert(root_ca);
client.setServer(mqtt_server, 8883);
```

---

##  Test de fonctionnement

Sous Raspberry Pi :

```bash
mosquitto_sub -h x.x.x.x -p 8883 -t thermoguard/# \
--cafile /etc/mosquitto/certs/ca.crt \
-u xxxx -P 'motdepasse'
```

---

##  Résultat obtenu

Grâce à cette configuration :

* les communications MQTT sont **chiffrées (TLS)**
* l’accès est **protégé par authentification**
* les données sont **sécurisées contre l’interception**

---

##  Conclusion

La mise en place du protocole TLS permet de transformer MQTT en un protocole sécurisé adapté à un environnement réel.

Ce mécanisme est essentiel dans un système IoT afin de garantir la protection des données et la fiabilité des communications.
