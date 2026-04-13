#include "mqtt.h"
#include "motores.h"
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient    espClient;
PubSubClient  client(espClient);
QueueHandle_t _colaMotores;

void onMessage(char* topic, byte* payload, unsigned int length) {
    StaticJsonDocument<256> doc;
    if (deserializeJson(doc, payload, length)) return;

    const char* accion    = doc["accion"];
    float       confianza = doc["confianza"];
    const char* fuente    = doc["fuente"];

    Serial.printf("[%s] %s (%.0f%%)\n", fuente, accion, confianza * 100);

    AccionMotor cmd;
    if      (strcmp(accion, "avanzar")   == 0) cmd = ACCION_AVANZAR;
    else if (strcmp(accion, "frenar")    == 0) cmd = ACCION_FRENAR;
    else if (strcmp(accion, "girar_izq") == 0) cmd = ACCION_GIRAR_IZQ;
    else if (strcmp(accion, "girar_der") == 0) cmd = ACCION_GIRAR_DER;
    else                                        cmd = ACCION_FRENAR;
    xQueueOverwrite(_colaMotores, &cmd);
}

void iniciarMQTT(QueueHandle_t colaMotores) {
    _colaMotores = colaMotores;

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("WiFi conectado");

    client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
    client.setCallback(onMessage);

    while (!client.connected()) {
        Serial.print("Conectando a MQTT...");
        if (client.connect("ESP32Robot")) {
            client.subscribe(TOPIC_ACTION);
            Serial.println("OK");
        } else {
            Serial.printf("fallo rc=%d\n", client.state());
            delay(5000);
        }
    }
}

void publicarSensores(DatosSensores datos) {
    String payload = "{";
    payload += "\"distancia\":{";
    payload += "\"frente\":"    + String(datos.distFrente) + ",";
    payload += "\"derecha\":"   + String(datos.distDer)    + ",";
    payload += "\"izquierda\":" + String(datos.distIzq);
    payload += "},\"altura\":{";
    payload += "\"izquierda\":" + String(datos.tcrtIzq) + ",";
    payload += "\"derecha\":"   + String(datos.tcrtDer);
    payload += "}}";
    client.publish(TOPIC_SENSORES, payload.c_str());
}

void publicarAire(DatosAire aire) {
    String payload = "{\"aire\":{";
    payload += "\"valor\":"    + String(aire.valor) + ",";
    payload += "\"calidad\":\"" + String(aire.calidad) + "\"}}";
    client.publish(TOPIC_AIRE, payload.c_str());
}