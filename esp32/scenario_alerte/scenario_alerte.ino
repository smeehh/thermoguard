#include <DHT.h>

#define DHTPIN 14
#define DHTTYPE DHT22

#define LED_PIN 25
#define BUZZER_PIN 26

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("SCENARIO 2 : Seuil critique > 15C");
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Erreur DHT22");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C | Humidite: ");
  Serial.print(h);
  Serial.println(" %");

  // Seuil critique fixé à 15°C
  if (t > 15) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
    Serial.println("ALERTE ACTIVE (seuil depasse)");
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    Serial.println("Temperature normale");
  }

  delay(2000);
}
