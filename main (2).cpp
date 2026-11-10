/*
 * Ex 1 - Etapa 3: Fade de ida e volta com millis()
 *
 * Mesmo comportamento da Etapa 2 (sobe até 255, desce até 0), mas sem
 * delay(): o programa só atualiza o brilho quando passam INTERVALO ms,
 * deixando o loop() livre para outras tarefas.
 *
 * Circuito:
 *   pino 9 (~PWM) → resistor 220 Ω → LED → GND
 */

#include <Arduino.h>

const int PINO_LED = 9;
const unsigned long INTERVALO = 30;  // ms entre cada passo

int brilho = 0;
int passo = 5;
unsigned long ultimaAtualizacao = 0;

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();

  if (agora - ultimaAtualizacao >= INTERVALO) {
    ultimaAtualizacao = agora;

    analogWrite(PINO_LED, brilho);
    Serial.println(brilho);

    brilho += passo;

    if (brilho >= 255) {
      brilho = 255;
      passo = -passo;
    } else if (brilho <= 0) {
      brilho = 0;
      passo = -passo;
    }
  }

  // Outras tarefas podem rodar aqui sem travar o fade.
}
