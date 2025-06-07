// Librerias y Variable.h
#include <QTRSensors.h>
#include "variable.h"
#include <BluetoothSerial.h>

/* Bluetooth */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Fallo de Bluetooth
#endif

/* -- Variables de Librerias -- */
BluetoothSerial SerialBT;
QTRSensors QTR;

/* ------ Variables INT ------ */
int umbral = 3000;
int posicion;

/* -- Variables Sensores -- */
const uint8_t SensorNum = 8;
uint16_t sensorValues[SensorNum];

/* -- Variables para limitar los valores de la ESP32 -- */
const int freq = 5000;
const int resolution = 8;

void setup() {
    SerialBT.begin("Balatro Dinamico");
    motorSetup();
    // Serial.begin(9600);
    /* QTR Setup */
    QTR.setTypeAnalog();
    QTR.setSensorPins((const uint8_t[]){36, 39, 34, 35, 32, 33, 25, 26}, SensorNum);
    QTR.setEmitterPin(27);
    /* CALIBRACION SENSOR */
    while(digitalRead(BOTON) == 0) {
        delay(10);
    }
    SerialBT.println("- Se ha inicializado la Calibracion -");
    delay(500);
    pinMode(LED, OUTPUT);
    pinMode(BOTON, INPUT);
    digitalWrite(LED, HIGH);
    for(int i = 0; i < 200; i++) {
        QTR.calibrate();
        delay(10);
    }
    digitalWrite(LED, LOW);
    SerialBT.println("- CALIBRACION TERMINADA -");
    while(digitalRead(BOTON) == 0) {
        delay(10);
    }
    delay(1000);
}

void loop() {
    DynamicPosition();
    PositionFollow();
}