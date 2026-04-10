#include "aire.h"
#include "config.h"
#include <Arduino.h>
void iniciarAire() {
    pinMode(MQ135_PIN, INPUT);
}
DatosAire leerAire() {
    DatosAire datos;
    datos.valor = analogRead(MQ135_PIN);
    if (datos.valor < 1000) {
        datos.calidad = "BUENA";
    } else if (datos.valor < 2000) {
        datos.calidad = "REGULAR";
    } else if (datos.valor < 3000) {
        datos.calidad = "MALA";
    } else {
        datos.calidad = "MUY MALA";
    }
    return datos;
}