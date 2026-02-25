# Configuration et vérification de Tailscale (VPN)

## 1. Contexte

Dans le cadre du projet BTS CIEL, l'accès au Raspberry Pi est sécurisé via un VPN.
Tailscale permet un accès distant sécurisé sans exposer le Raspberry Pi directement sur Internet.

IP VPN attribuée au Raspberry Pi :
IP_VPN_RASPBERRY

---

## 2. Installation de Tailscale

Installation :

curl -fsSL https://tailscale.com/install.sh | sh

Connexion au réseau Tailscale :

sudo tailscale up

Une authentification via navigateur est nécessaire lors de la première configuration.

---

## 3. Vérification du statut

Vérification de l’état du service :

tailscale status

Vérification de l’adresse IP VPN :

tailscale ip -4

Résultat attendu :
IP_VPN_RASPBERRY

---

## 4. Test de connexion SSH via VPN

Connexion distante depuis un poste client :

ssh pi@IP_VPN_RASPBERRY

Cela permet un accès sécurisé au Raspberry Pi via le réseau privé Tailscale.

---

## 5. Conclusion

Le Raspberry Pi est accessible via un VPN sécurisé.
Aucun port n’est exposé directement sur Internet.
L’accès distant au serveur est donc sécurisé et maîtrisé.
