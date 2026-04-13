#pragma once

enum AccionMotor {
    ACCION_AVANZAR,
    ACCION_FRENAR,
    ACCION_GIRAR_IZQ,
    ACCION_GIRAR_DER
};

void iniciarMotores();
void avanzar();
void frenar();
void girarIzquierda();
void girarDerecha();