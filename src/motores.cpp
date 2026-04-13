#include "motores.h"
#include "config.h"
#include <Arduino.h>

void iniciarMotores() {
    pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

    ledcSetup(PWM_CANAL_A, PWM_FREQ, PWM_BITS);
    ledcSetup(PWM_CANAL_B, PWM_FREQ, PWM_BITS);
    ledcAttachPin(ENA, PWM_CANAL_A);
    ledcAttachPin(ENB, PWM_CANAL_B);

    frenar();
}

void avanzar() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    ledcWrite(PWM_CANAL_A, VELOCIDAD);
    ledcWrite(PWM_CANAL_B, VELOCIDAD);
}

void frenar() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    ledcWrite(PWM_CANAL_A, 0);
    ledcWrite(PWM_CANAL_B, 0);
}

void girarIzquierda() {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    ledcWrite(PWM_CANAL_A, VELOCIDAD);
    ledcWrite(PWM_CANAL_B, VELOCIDAD);
}

void girarDerecha() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
    ledcWrite(PWM_CANAL_A, VELOCIDAD);
    ledcWrite(PWM_CANAL_B, VELOCIDAD);
}