/*
 * Ex 1 - Etapa 1: Fade com reinício
 *
 * O brilho do LED aumenta gradualmente de 0 até 255 (PWM).
 * Ao chegar em 255, volta imediatamente para 0 e recomeça.
 *
 * Circuito:
 *   pino 9 (~PWM) → resistor 220 Ω → LED → GND
 */

#include <Arduino.h>

const int PINO_LED = 9;  // precisa ser um pino PWM (~): 3, 5, 6, 9, 10 ou 11
const int PASSO = 5;     // quanto o brilho aumenta por vez
const int ATRASO = 30;   // ms entre cada passo

int brilho = 0;

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(PINO_LED, brilho);
  Serial.println(brilho);

  brilho += PASSO;

  if (brilho > 255) {
    brilho = 0;  // chegou em 255 → volta a 0
  }

  delay(ATRASO);
}
