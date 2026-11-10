/*
 * Ex 1 - Etapa 2: Fade de ida e volta
 *
 * O brilho sobe de 0 até 255 e, ao chegar em 255, começa a diminuir
 * gradualmente até 0. Depois sobe de novo, e assim por diante ("respiração").
 *
 * Circuito:
 *   pino 9 (~PWM) → resistor 220 Ω → LED → GND
 */

#include <Arduino.h>

const int PINO_LED = 9;
const int ATRASO = 30;  // ms entre cada passo

int brilho = 0;
int passo = 5;  // positivo = subindo, negativo = descendo

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(PINO_LED, brilho);
  Serial.println(brilho);

  brilho += passo;

  // Chegou em um dos extremos → inverte o sentido
  if (brilho >= 255) {
    brilho = 255;
    passo = -passo;  // começa a diminuir
  } else if (brilho <= 0) {
    brilho = 0;
    passo = -passo;  // começa a aumentar
  }

  delay(ATRASO);
}
