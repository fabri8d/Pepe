#include "mqtt.h"
#include "sensores.h"
#include "aire.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t colaSensores;
QueueHandle_t colaAire;

void tareaSensores(void *pvParameters) {
    while (true) {
        DatosSensores datos = leerSensores();
        xQueueSend(colaSensores, &datos, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void tareaAire(void *pvParameters) {
    while (true) {
        DatosAire aire = leerAire();
        xQueueSend(colaAire, &aire, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(5000));
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
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
void setup() {
    Serial.begin(9600);
    iniciarSensores();
    iniciarAire();
    colaSensores = xQueueCreate(10, sizeof(DatosSensores));
    colaAire = xQueueCreate(10, sizeof(DatosAire));
    iniciarMQTT();
    xTaskCreatePinnedToCore(tareaSensores, "Sensores", 4096, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(tareaAire, "Aire", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(tareaMQTT, "MQTT", 4096, NULL, 1, NULL, 1);
}
void loop() {}