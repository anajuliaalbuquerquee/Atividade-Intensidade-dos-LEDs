/*
 * Ex 2 - Etapa 1: DHT com alertas de temperatura e umidade
 *
 * Lê temperatura e umidade do sensor DHT11 (ou DHT22):
 *   - temperatura > TEMP_LIMITE  → LED vermelho aceso
 *   - umidade     > UMID_LIMITE  → LED azul aceso
 * Mostra as leituras no Monitor Serial.
 *
 * Biblioteca: "DHT sensor library" (Adafruit) — já declarada no platformio.ini.
 *
 * Circuito:
 *   DHT11 (3 pinos): VCC → 5V, DATA → pino 2, GND → GND
 *     (módulo de 4 pinos: resistor 10 kΩ entre DATA e 5V)
 *   LED vermelho: pino 9  → 220 Ω → LED → GND
 *   LED azul:     pino 10 → 220 Ω → LED → GND
 */

#include <Arduino.h>
#include <DHT.h>

const int PINO_DHT = 2;
#define TIPO_DHT DHT11   // troque para DHT22 se for o seu sensor

const int LED_VERMELHO = 9;
const int LED_AZUL = 10;

const float TEMP_LIMITE = 28.0;  // °C
const float UMID_LIMITE = 70.0;  // %

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperatura = dht.readTemperature();  // °C
  float umidade = dht.readHumidity();         // %

  // O DHT às vezes falha na leitura; nesse caso ignora esta volta
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha ao ler o DHT!");
    delay(2000);
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" C  |  Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  if (temperatura > TEMP_LIMITE) {
    digitalWrite(LED_VERMELHO, HIGH);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
  }

  if (umidade > UMID_LIMITE) {
    digitalWrite(LED_AZUL, HIGH);
  } else {
    digitalWrite(LED_AZUL, LOW);
  }

  delay(2000);  // o DHT11 só consegue uma leitura a cada ~2 s
}
