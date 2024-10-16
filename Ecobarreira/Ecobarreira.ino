#include <Stepper.h>

const int stepsPerRevolution = 2048;

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

const int trigPin = 12;
const int echoPin = 13;

const int ledPin = 3;

long duration;
int distance;

void setup() {

  myStepper.setSpeed(15);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  Serial.println("Sistema iniciado.");
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 5) {

    digitalWrite(ledPin, HIGH);
    

    Serial.println("Objeto detectado! Motor girando 90° e LED aceso...");
    myStepper.step(512);

    delay(500);

    Serial.println("Retornando à posição inicial...");
    myStepper.step(-512);

    digitalWrite(ledPin, LOW);
  } else {
    Serial.println("Distância maior que 5 cm. Motor parado e LED apagado.");
  }

  delay(10);
}
