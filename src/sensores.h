#pragma once
struct DatosSensores {
    long distFrente;
    long distDer;
    long distIzq;
    int  tcrtIzq;
    int  tcrtDer;
};

void iniciarSensores();
DatosSensores leerSensores();