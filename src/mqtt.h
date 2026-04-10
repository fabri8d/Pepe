#pragma once
#include "aire.h"
#include "sensores.h"
#include <PubSubClient.h>
extern PubSubClient client;

void iniciarMQTT();
void publicarSensores(DatosSensores datos);
void publicarAire(DatosAire aire);