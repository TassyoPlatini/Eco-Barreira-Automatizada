#include <Stepper.h>   // Biblioteca para controle de motor de passo

// Definindo o número de passos por revolução (ajuste conforme o seu motor)
const int stepsPerRevolution = 2048;  // Para o 28BYJ-48, 2048 passos por revolução

// Definindo os pinos para o motor de passo
const int IN1 = 8;  // Entrada 1 do ULN2003 conectada à porta 1 do Arduino
const int IN2 = 9;  // Entrada 2 do ULN2003 conectada à porta 2 do Arduino
const int IN3 = 10;  // Entrada 3 do ULN2003 conectada à porta 3 do Arduino
const int IN4 = 11;  // Entrada 4 do ULN2003 conectada à porta 4 do Arduino

// Criando o objeto Stepper com a sequência correta de pinos
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);  // Ordem ajustada para IN1, IN3, IN2, IN4

// Definindo os pinos do sensor ultrassônico
const int trigPin = 12;  // Pino trig na porta 12
const int echoPin = 13;   // Pino echo na porta 13

// Definindo o pino do LED
const int ledPin = 3;  // LED conectado na porta 3

// Variáveis para distância
long duration;
int distance;

void setup() {
  // Inicializando o motor de passo com uma velocidade de 15 RPM
  myStepper.setSpeed(15);  // Diminuí a velocidade para garantir maior torque

  // Inicializando os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurando o LED como saída
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Certifica-se de que o LED comece desligado

  // Inicializando a comunicação serial
  Serial.begin(9600);
  Serial.println("Sistema iniciado.");
}

void loop() {
  // Gera o pulso do sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcula o tempo de ida e volta do pulso
  duration = pulseIn(echoPin, HIGH);

  // Converte o tempo em distância (em cm)
  distance = duration * 0.034 / 2;

  // Exibe a distância no monitor serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Verifica se a distância é menor ou igual a 5 cm
  if (distance <= 5) {
    // Acende o LED
    digitalWrite(ledPin, HIGH);
    
    // Gira o motor 90° (512 passos)
    Serial.println("Objeto detectado! Motor girando 90° e LED aceso...");
    myStepper.step(512);  // Gira 90° no sentido horário

    // Pequena pausa
    delay(500);

    // Retorna o motor para a posição inicial (gira 90° no sentido anti-horário)
    Serial.println("Retornando à posição inicial...");
    myStepper.step(-512);  // Gira 90° no sentido anti-horário

    // Apaga o LED após o movimento
    digitalWrite(ledPin, LOW);
  } else {
    Serial.println("Distância maior que 5 cm. Motor parado e LED apagado.");
  }

  delay(10); // Pequena pausa antes de medir novamente
}
