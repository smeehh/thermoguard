#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// ---------------- WIFI ----------------
const char* ssid = "xxxxxx";
const char* password = "xxxxx";

// ---------------- MQTT ----------------
const char* mqtt_server = "x.x.x.x";
const int mqtt_port = 8883;
const char* mqtt_user = "x";
const char* mqtt_password = "x";

// ---------------- CERTIFICAT TLS ----------------
static const char *root_ca = R"EOF(
-----BEGIN CERTIFICATE-----
xxxxxxxxxxxxxxxxxxxxxxxxxxx
-----END CERTIFICATE-----
)EOF";

// ---------------- DHT22 ----------------
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------------- LED + BUZZER ----------------
#define LED_PIN 25
#define BUZZER_PIN 26

// ---------------- CLIENTS ----------------
WiFiClientSecure espClient;
PubSubClient client(espClient);

// ---------------- WIFI ----------------
void setup_wifi() {
  Serial.println("=== ETAPE 1 : CONNEXION WIFI ===");
  Serial.print("Connexion au reseau : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Statut Wi-Fi : ");
    Serial.println(WiFi.status());
  }

  Serial.println("Wi-Fi connecte");
  Serial.print("Adresse IP ESP32 : ");
  Serial.println(WiFi.localIP());
}

// ---------------- RECEPTION MQTT ----------------
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message recu sur topic : ");
  Serial.println(topic);
  Serial.print("Contenu : ");
  Serial.println(message);

  if (String(topic) == "thermoguard/alerte") {
    if (message == "ON") {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("ALERTE ACTIVE : LED + BUZZER ON");
    } 
    else if (message == "OFF") {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("ALERTE DESACTIVEE : LED + BUZZER OFF");
    }
  }
}

// ---------------- MQTT ----------------
void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.println("=== ETAPE 2 : CONNEXION MQTT TLS ===");
    Serial.print("Tentative vers broker : ");
    Serial.println(mqtt_server);

    if (client.connect("ESP32ClientTLS", mqtt_user, mqtt_password)) {
      Serial.println("Connecte au broker MQTT TLS");

      client.publish("thermoguard/test", "ESP32 connecte en TLS");
      Serial.println("Message test envoye sur thermoguard/test");

      client.subscribe("thermoguard/alerte");
      Serial.println("Abonne au topic thermoguard/alerte");
    } else {
      Serial.print("Echec MQTT, code = ");
      Serial.println(client.state());
      Serial.println("Nouvelle tentative dans 2 secondes...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== DEMARRAGE PROGRAMME ===");

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();
  setup_wifi();

  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }

  client.loop();

  float temperature = dht.readTemperature();
  float humidite = dht.readHumidity();

  if (isnan(temperature) || isnan(humidite)) {
    Serial.println("Erreur lecture DHT22");
  } else {
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);

    char humString[8];
    dtostrf(humidite, 1, 2, humString);

    client.publish("thermoguard/temperature", tempString);
    client.publish("thermoguard/humidite", humString);

    Serial.print("Temperature envoyee : ");
    Serial.println(tempString);

    Serial.print("Humidite envoyee : ");
    Serial.println(humString);
  }

  delay(5000);
}
