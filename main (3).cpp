/*
 * Ex 1 - Etapa 4: 3 LEDs acendendo em sequência e de forma gradual
 *
 * Um LED por vez faz o fade completo (0 → 255 → 0). Quando termina,
 * passa para o próximo LED: 1 → 2 → 3 → 1 → ...  Tudo com millis().
 *
 * Circuito (todos em pinos PWM ~):
 *   pino 9  → 220 Ω → LED 1 → GND
 *   pino 10 → 220 Ω → LED 2 → GND
 *   pino 11 → 220 Ω → LED 3 → GND
 */

#include <Arduino.h>

const int NUM_LEDS = 3;
const int PINOS_LED[NUM_LEDS] = {9, 10, 11};
const unsigned long INTERVALO = 10;  // ms entre cada passo

int ledAtual = 0;   // índice do LED que está fazendo o fade
int brilho = 0;
int passo = 5;
unsigned long ultimaAtualizacao = 0;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(PINOS_LED[i], OUTPUT);
    analogWrite(PINOS_LED[i], 0);
  }
  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();

  if (agora - ultimaAtualizacao >= INTERVALO) {
    ultimaAtualizacao = agora;

    analogWrite(PINOS_LED[ledAtual], brilho);

    brilho += passo;

    if (brilho >= 255) {
      brilho = 255;
      passo = -passo;             // chegou no máximo → começa a apagar
    } else if (brilho <= 0) {
      brilho = 0;
      passo = -passo;
      analogWrite(PINOS_LED[ledAtual], 0);   // garante apagado
      ledAtual = (ledAtual + 1) % NUM_LEDS;  // próximo LED da sequência
      Serial.print("LED ");
      Serial.println(ledAtual + 1);
    }
  }
}

/*
 * Variante "onda" (um LED começa a acender enquanto o anterior apaga):
 * use um brilho e um passo por LED, deslocados no tempo, e atualize os três
 * no mesmo bloco de millis().
 */
