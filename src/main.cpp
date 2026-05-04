#include "mqtt.h"
#include "sensores.h"
#include "aire.h"
#include "motores.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t colaSensores;
QueueHandle_t colaAire;
QueueHandle_t colaMotores;

void tareaSensores(void *pvParameters) {
    while (true) {
        DatosSensores datos = leerSensores();
        xQueueSend(colaSensores, &datos, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void tareaMotores(void *pvParameters) {
    AccionMotor accion;
    while (true) {
        if (xQueueReceive(colaMotores, &accion, portMAX_DELAY)) {
            switch (accion) {
                case ACCION_AVANZAR:   avanzar();        break;
                case ACCION_FRENAR:    frenar();         break;
                case ACCION_GIRAR_IZQ: girarIzquierda(); break;
                case ACCION_GIRAR_DER: girarDerecha();   break;
                default:               frenar();         break;
            }
        }
    }
}

void tareaAire(void *pvParameters) {
    while (true) {
        DatosAire aire = leerAire();
        xQueueSend(colaAire, &aire, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

void tareaMQTT(void *pvParameters) {
    while (true) {
        DatosSensores datos;
        DatosAire aire;
        client.loop();
        if (xQueueReceive(colaSensores, &datos, 0)) {
            publicarSensores(datos);
        }
        if (xQueueReceive(colaAire, &aire, 0)) {
            publicarAire(aire);
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void setup() {
    iniciarSensores();
    iniciarAire();
    iniciarMotores();

    colaSensores = xQueueCreate(5, sizeof(DatosSensores));
    colaAire     = xQueueCreate(2, sizeof(DatosAire));
    colaMotores  = xQueueCreate(1, sizeof(AccionMotor));

    iniciarMQTT(colaMotores);
    sleep(20);
    // Core 0 — hardware físico
    xTaskCreatePinnedToCore(tareaSensores, "Sensores", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(tareaMotores,  "Motores",  2048, NULL, 3, NULL, 0);

    // Core 1 — comunicación
    xTaskCreatePinnedToCore(tareaMQTT, "MQTT", 8192, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(tareaAire, "Aire", 2048, NULL, 1, NULL, 1);
}

void loop() {}