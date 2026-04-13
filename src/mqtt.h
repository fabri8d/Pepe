#pragma once
#include "aire.h"
#include "sensores.h"
#include "motores.h"
#include <PubSubClient.h>
#include <freertos/queue.h>

extern PubSubClient client;

void iniciarMQTT(QueueHandle_t colaMotores);
void publicarSensores(DatosSensores datos);
void publicarAire(DatosAire aire);