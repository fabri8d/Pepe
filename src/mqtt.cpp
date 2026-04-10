#include "mqtt.h"
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

void iniciarMQTT() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("WiFi conectado");

    client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
    
    while (!client.connected()) { 
        Serial.print("Conectando a MQTT...");
        if (client.connect("ESP32Robot")) {
            Serial.println("MQTT conectado");
        } else {
            Serial.print("fallo, rc=");
            Serial.print(client.state());
            Serial.println(" reintentando en 5 seg...");
            delay(5000);
        }
    }
}
void publicarSensores(DatosSensores datos) {
    
    String payloadSensores = "{";
    payloadSensores += "\"distancia\":{";
    payloadSensores += "\"frente\":" + String(datos.distFrente) + ",";
    payloadSensores += "\"derecha\":" + String(datos.distDer) + ",";
    payloadSensores += "\"izquierda\":" + String(datos.distIzq);
    payloadSensores += "},";
    payloadSensores += "\"altura\":{";
    payloadSensores += "\"izquierda\":" + String(datos.tcrtIzq) + ",";
    payloadSensores += "\"derecha\":" + String(datos.tcrtDer);
    payloadSensores += "}}";

    client.publish(TOPIC_SENSORES, payloadSensores.c_str());
}
void publicarAire(DatosAire aire) {
    String payloadAire = "{";
    payloadAire += "\"aire\":{";
    payloadAire += "\"valor\":" + String(aire.valor) + ",";
    payloadAire += "\"calidad\":\"" + String(aire.calidad) + "\"";
    payloadAire += "}}";
    client.publish(TOPIC_AIRE, payloadAire.c_str());
}