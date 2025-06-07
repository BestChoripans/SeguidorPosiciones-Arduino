/* ---- FUNCIONES DE UTILIDAD ---- */
#include "variable.h"

void ReadQTR() {
    /* -- LECTURA QTRSensors -- */
    QTR.read(sensorValues); // <--- Dependiendo de como nombraste la variable de QTRSensors va a ser distinta esta parte
    for(int i=0;i<8;i++){
        if(sensorValues[i]>umbral){
            SerialBT.print("□ (");
            SerialBT.print(sensorValues[i]);
            SerialBT.print(")");
        } else {
            SerialBT.print("■ (");
            SerialBT.print(sensorValues[i]);
            SerialBT.print(")");
        } 
        SerialBT.print("\t");
    }
    SerialBT.println();
    delay(100);
}

void TestMotor() {
    /* -- Test de los motores -- */
    for(int i = 0; i < 3; i++){ // <--- ejecuta 3 veces el siguente codigo
        motores(100, 100); // <--- Esta parte cambia dependiendo del nombre de la funcion de los motores
        delay(500);
        motores(50, 100);
        delay(500);
        motores(100, 50);
        delay(500);
        motores(-100, -100);
        delay(500);
    }
}

void TestAll(){
    /* --- Test de motores y Lectura de QTR --- */ 
    for(int i = 0; i < 3; i++){ // <--- ejecuta 3 veces el siguente codigo
        motores(100, 100); // <--- Esta parte cambia dependiendo del nombre de la funcion de los motores
        delay(500);
        motores(50, 100);
        delay(500);
        motores(100, 50);
        delay(500);
        motores(-100, -100);
        delay(500);
    }
    SerialBT.println("Test Motor TERMINADO - Pulse el boton para seguir con la Lectura QTR");
    while(digitalRead(BOTON) == 0) { // <--- Fijate el nombre de la variable de boton y cambialo si la tienes a otro nombre
        delay(10);
    }
    for(int t = 0; t < 100; t++){
        QTR.read(sensorValues); // <--- Dependiendo de como nombraste la variable de QTRSensors va a ser distinta esta parte
        for(int i=0;i<8;i++){
            if(sensorValues[i]>umbral){
                SerialBT.print("□ (");
                SerialBT.print(sensorValues[i]);
                SerialBT.print(")");
            } else {
                SerialBT.print("■ (");
                SerialBT.print(sensorValues[i]);
                SerialBT.print(")");
            } 
            SerialBT.print("\t");
        }
        SerialBT.println();
        delay(100);
    }
}


void DynamicPosition(){
    /* LECTURA DE LA POSICION */
    QTR.read(sensorValues);
    posicion = QTR.readLineBlack(sensorValues);

    posicion = map(posicion, 0, 7000, -255, 255);

    SerialBT.println(posicion);
    delay(250);
}

/* ---- FUNCIONES PARA SEGUIDORES DE LINEA ---- */

void PositionFollow(){
    if(posicion>-40 && posicion<20){
        motores(30,30);
        SerialBT.println("<- Avanzando ->");
    } else if(posicion>20){
        motores(25,5);
        SerialBT.println("<- Derecha ->");
    } else if(posicion>-130 && posicion<-40){
        motores(5,25);
        SerialBT.println("<- Izquierda ->");
    }
}

void error(){
    delay(300);
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
    delay(300);
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
    delay(300);
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
}