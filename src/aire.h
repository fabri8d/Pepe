#pragma once
#include <Arduino.h>

struct DatosAire
{
    int valor;
    String calidad;
};
void iniciarAire();
DatosAire leerAire();