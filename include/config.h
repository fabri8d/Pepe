#pragma once

// WIFI
constexpr const char* WIFI_SSID_STR     = WIFI_SSID;
constexpr const char* WIFI_PASSWORD_STR = WIFI_PASSWORD;

// MQTT
constexpr const char* MQTT_SERVER_IP_STR = MQTT_SERVER_IP;
const int MQTT_SERVER_PORT_VAL = MQTT_SERVER_PORT;
constexpr const char* TOPIC_SENSORES = "robot/sensores";
constexpr const char* TOPIC_AIRE     = "robot/aire";
constexpr const char* TOPIC_ACTION = "robot/action";

// HC-SR04
const int TRIG_FRENTE = 15;
const int ECHO_FRENTE = 2;
const int TRIG_DER    = 4;
const int ECHO_DER    = 16;
const int TRIG_IZQ    = 17;
const int ECHO_IZQ    = 5;

// TCRT5000
const int TCRT_IZQ = 36;
const int TCRT_DER = 34;

// MQ-135
const int MQ135_PIN = 35;

const int IN1 = 19;
const int IN2 = 18;
const int IN3 = 21;
const int IN4 = 22;
const int ENA = 33;
const int ENB = 32;

// PWM
const int PWM_CANAL_A = 2;
const int PWM_CANAL_B = 3;
const int PWM_FREQ    = 1000;
const int PWM_BITS    = 8;
const int VELOCIDAD_IZQUIERDA   = 90;
const int VELOCIDAD_DERECHA   = 89;

 