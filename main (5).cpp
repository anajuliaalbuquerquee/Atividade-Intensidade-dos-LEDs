/*
 * Ex 2 - Etapa 2: Intensidade dos LEDs proporcional ao DHT
 *
 * A intensidade (PWM) de cada LED acompanha a leitura do sensor:
 *   - LED vermelho: quanto maior a temperatura, mais forte
 *   - LED azul:     quanto maior a umidade, mais forte
 *
 * Usa map() para converter a faixa do sensor em 0..255 e constrain() para
 * não passar dos limites.
 *
 * Circuito: o mesmo da Etapa 1 (LEDs em pinos PWM ~).
 *   DHT11: VCC → 5V, DATA → pino 2, GND → GND
 *   LED vermelho: pino 9  → 220 Ω → LED → GND
 *   LED azul:     pino 10 → 220 Ω → LED → GND
 */

#include <Arduino.h>
#include <DHT.h>

const int PINO_DHT = 2;
#define TIPO_DHT DHT11   // troque para DHT22 se for o seu sensor

const int LED_VERMELHO = 9;
const int LED_AZUL = 10;

// Faixas usadas para o mapeamento (ajuste ao seu ambiente)
const int TEMP_MIN = 15;   // °C → brilho 0
const int TEMP_MAX = 35;   // °C → brilho 255
const int UMID_MIN = 20;   // %  → brilho 0
const int UMID_MAX = 90;   // %  → brilho 255

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha ao ler o DHT!");
    delay(2000);
    return;
  }

  // Converte a leitura para 0..255 e garante que fique dentro da faixa
  int brilhoVermelho = map((int)temperatura, TEMP_MIN, TEMP_MAX, 0, 255);
  int brilhoAzul = map((int)umidade, UMID_MIN, UMID_MAX, 0, 255);
  brilhoVermelho = constrain(brilhoVermelho, 0, 255);
  brilhoAzul = constrain(brilhoAzul, 0, 255);

  analogWrite(LED_VERMELHO, brilhoVermelho);
  analogWrite(LED_AZUL, brilhoAzul);

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" C -> LED vermelho ");
  Serial.print(brilhoVermelho);
  Serial.print("  |  Umidade: ");
  Serial.print(umidade);
  Serial.print(" % -> LED azul ");
  Serial.println(brilhoAzul);

  delay(2000);
}
