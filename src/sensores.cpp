#include "sensores.h"
#include "config.h"
#include <Arduino.h>

void iniciarSensores() {
    pinMode(TRIG_FRENTE, OUTPUT);
    pinMode(ECHO_FRENTE, INPUT);
    pinMode(TRIG_DER, OUTPUT);
    pinMode(ECHO_DER, INPUT);
    pinMode(TRIG_IZQ, OUTPUT);
    pinMode(ECHO_IZQ, INPUT);
    pinMode(TCRT_IZQ, INPUT);
    pinMode(TCRT_DER, INPUT);
}

long medirDistancia(int trig, int echo) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long duracion = pulseIn(echo, HIGH, 30000);
    return duracion / 58;
}

DatosSensores leerSensores(){
    DatosSensores datos;
    datos.distFrente = medirDistancia(TRIG_FRENTE, ECHO_FRENTE);
    datos.distDer    = medirDistancia(TRIG_DER, ECHO_DER);
    datos.distIzq   = medirDistancia(TRIG_IZQ, ECHO_IZQ);
    int infrarojoIzq = analogRead(TCRT_IZQ);
    int infrarojoDer = analogRead(TCRT_DER);
    if (infrarojoDer > 500){datos.tcrtDer = 1;}
    else{datos.tcrtDer = 0;}
    if (infrarojoIzq > 500){datos.tcrtIzq = 1;}
    else{datos.tcrtIzq = 0;}
    return datos;
}