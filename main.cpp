#include <Arduino.h>
#include <DHT.h>

// Definição dos pinos
#define PIN_FOSFORO 12    // Botão Fósforo (P)
#define PIN_POTASSIO 14   // Botão Potássio (K)
#define PIN_LDR 34        // LDR (pH)
#define PIN_DHT 27        // DHT22 (umidade)
#define PIN_RELE 26       // Relé (bomba)

// Inicialização do sensor DHT
#define DHTTYPE DHT22
DHT dht(PIN_DHT, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(PIN_FOSFORO, INPUT_PULLUP);
  pinMode(PIN_POTASSIO, INPUT_PULLUP);
  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_RELE, OUTPUT);

  dht.begin();
  digitalWrite(PIN_RELE, LOW); // Bomba desligada inicialmente
}

void loop() {
  // Leitura dos sensores
  bool fosforo = digitalRead(PIN_FOSFORO) == LOW;   // Pressionado = presença
  bool potassio = digitalRead(PIN_POTASSIO) == LOW; // Pressionado = presença
  int ldrValue = analogRead(PIN_LDR);               // Valor analógico do LDR
  float ph = map(ldrValue, 0, 4095, 0, 14);         // Simulação de pH (0-14)
  float umidade = dht.readHumidity();               // Umidade do solo

  // Lógica de controle da bomba:
  // Exemplo: Liga se umidade < 40% e ambos nutrientes presentes
  bool ligarBomba = (umidade < 40.0) && fosforo && potassio;

  digitalWrite(PIN_RELE, ligarBomba ? HIGH : LOW);

  // Exibe dados no monitor serial (formato legível)
  Serial.print("Fosforo: "); Serial.print(fosforo ? "Presente" : "Ausente");
  Serial.print(" | Potassio: "); Serial.print(potassio ? "Presente" : "Ausente");
  Serial.print(" | pH: "); Serial.print(ph, 1);
  Serial.print(" | Umidade: "); Serial.print(umidade, 1);
  Serial.print(" | Bomba: "); Serial.println(ligarBomba ? "Ligada" : "Desligada");

  // Envia dados em formato CSV para integração com Python
  // Formato: fosforo,potassio,ph,umidade,bomba
  Serial.print("CSV:");
  Serial.print(fosforo ? 1 : 0); Serial.print(",");
  Serial.print(potassio ? 1 : 0); Serial.print(",");
  Serial.print(ph, 1); Serial.print(",");
  Serial.print(umidade, 1); Serial.print(",");
  Serial.println(ligarBomba ? 1 : 0);

  delay(2000); // Aguarda 2 segundos
}
