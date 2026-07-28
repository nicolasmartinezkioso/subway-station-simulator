/*
  Subway Station Simulator
  Simulates a subway line cycling through 4 stations plus a traveling state.
  Controls a 7-segment display, a servo motor (simulating door open/close),
  4 status LEDs, and a buzzer to represent train arrivals and departures.
  A debounced push-button starts and stops the simulation.
*/

#include <Servo.h>

#define BOTON 7
#define LEDAZUL 13
int estadoAnteriorBoton = 1;
bool estadoLED = false;
#define BUZZER 2
#define LEDCONSTITUCION 6
#define LEDSANJUAN 5
#define LEDINDEPENDENCIA 4
#define LEDMORENO 3
#define C A4
#define D A3
#define E A2
#define G 11
#define F 10
#define A 9
#define B 8
#define TIEMPO_ESTACION 1500
#define TIEMPO_TITILADO 300
#define EST_CONSTITUCION 20
#define EST_SANJUAN 21
#define EST_INDEPENDENCIA 22
#define EST_MORENO 23
#define EST_VIAJE 24
int estacionActual = EST_CONSTITUCION;
int estacionesFaltantes = 3;
bool incrementando = true;
Servo servoMotor;

void setup() {
  pinMode(LEDAZUL, OUTPUT);
  pinMode(BOTON, INPUT);
  estadoAnteriorBoton = 1;
  pinMode(LEDCONSTITUCION, OUTPUT);
  pinMode(LEDSANJUAN, OUTPUT);
  pinMode(LEDINDEPENDENCIA, OUTPUT);
  pinMode(LEDMORENO, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  apagarDisplay();
  apagarLeds();
  servoMotor.attach(12);
}

void loop() {
  actualizarEstadoBotonYLed();
  if (estadoLED) {
    manejarEstaciones();
  } else {
    apagarLeds();
    servoMotor.write(0);
  }
  delay(100);
}

// Main state machine: runs the sequence of station stops in order
void manejarEstaciones() {
  
  switch (estacionActual) {
    case EST_CONSTITUCION:
      apagarLeds();
      servoMotor.write(0);
      enViajeDisplay();
      delay(TIEMPO_ESTACION);
      apagarLeds();
      titilarLed(LEDCONSTITUCION);
      encenderLed(LEDCONSTITUCION);
      displayEnConstitucion();
      activarBuzzer();
      servoMotor.write(90);
      delay(TIEMPO_ESTACION);
      avanzarEstacion();
      break;
    case EST_SANJUAN:
      apagarLeds();
      servoMotor.write(0);
      enViajeDisplay();
      delay(TIEMPO_ESTACION);
      apagarLeds();
      titilarLed(LEDSANJUAN);
      encenderLed(LEDSANJUAN);
      displayEnSanJuan();
      activarBuzzer();
      servoMotor.write(90);
      delay(TIEMPO_ESTACION);
      avanzarEstacion();
      break;
    case EST_INDEPENDENCIA:
      apagarLeds();
      servoMotor.write(0);
      enViajeDisplay();
      delay(TIEMPO_ESTACION);
      apagarLeds();
      titilarLed(LEDINDEPENDENCIA);
      encenderLed(LEDINDEPENDENCIA);
      displayEnIndependencia();
      activarBuzzer();
      servoMotor.write(90);
      delay(TIEMPO_ESTACION);
      avanzarEstacion();
      break;
    case EST_MORENO:
      apagarLeds();
      servoMotor.write(0);
      enViajeDisplay();
      delay(TIEMPO_ESTACION);
      apagarLeds();
      titilarLed(LEDMORENO);
      encenderLed(LEDMORENO);
      displayEnMoreno();
      activarBuzzer();
      servoMotor.write(90);
      delay(TIEMPO_ESTACION);
      avanzarEstacion();
      break;
    case EST_VIAJE:
      apagarLeds();
      enViajeDisplay();
      delay(TIEMPO_ESTACION);
      servoMotor.write(0);
      avanzarEstacion();
      break;
  }
}

// Advances to the next station, alternating direction at the line's ends
void avanzarEstacion() {
  if (incrementando) {
    estacionesFaltantes--;
    if (estacionesFaltantes < 0) {
      estacionesFaltantes = 1;
      incrementando = false;
    }
  } else {
    estacionesFaltantes++;
    if (estacionesFaltantes > 3) {
      estacionesFaltantes = 2;
      incrementando = true;
    }
  }
  
  switch (estacionesFaltantes) {
    case 1:
      apagarLeds();
      estacionActual = EST_INDEPENDENCIA;
      break;
    case 2:
      apagarLeds();
      estacionActual = EST_SANJUAN;
      break;
    case 3:
      apagarLeds();
      estacionActual = EST_CONSTITUCION;
      break;
    case 0:
      apagarLeds();
      estacionActual = EST_MORENO;
      break;
  }
}

// Reads and debounces the button, toggling the simulation on/off via LEDAZUL
void actualizarEstadoBotonYLed() {
  int estadoActualBoton = digitalRead(BOTON);

  if (estadoActualBoton != estadoAnteriorBoton) {
    delay(50);
    estadoActualBoton = digitalRead(BOTON);

    if (estadoActualBoton == LOW) {
      estadoLED = !estadoLED;
      digitalWrite(LEDAZUL, estadoLED);
    }
  }
  estadoAnteriorBoton = estadoActualBoton;
}

// Turns off all 7-segment display segments
void apagarDisplay() {
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
}

// Displays the "in transit" symbol on the 7-segment display
void enViajeDisplay() {
  apagarDisplay();
  digitalWrite(G, LOW);
}

// Displays the "Constitución" station symbol
void displayEnConstitucion() {
  apagarDisplay();
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
}

// Displays the "San Juan" station symbol
void displayEnSanJuan() {
  apagarDisplay();
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(G, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
}

// Displays the "Independencia" station symbol
void displayEnIndependencia() {
  apagarDisplay();
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
}

// Displays the "Moreno" station symbol
void displayEnMoreno() {
  apagarDisplay();
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
}

// Turns off all station indicator LEDs
void apagarLeds() {
  digitalWrite(LEDCONSTITUCION, LOW);
  digitalWrite(LEDSANJUAN, LOW);
  digitalWrite(LEDINDEPENDENCIA, LOW);
  digitalWrite(LEDMORENO, LOW);
}

// Sounds the buzzer briefly to signal station arrival
void activarBuzzer() {
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
}

// Turns on a specific station LED
void encenderLed(int ledPin) {
  digitalWrite(ledPin, HIGH);
}

// Blinks a station LED to indicate arrival before staying lit
void titilarLed(int ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(TIEMPO_TITILADO);
  digitalWrite(ledPin, LOW);
  delay(TIEMPO_TITILADO);
  digitalWrite(ledPin, HIGH);
  delay(TIEMPO_TITILADO);
  digitalWrite(ledPin, LOW);
  delay(TIEMPO_TITILADO);
  digitalWrite(ledPin, HIGH);
  delay(TIEMPO_TITILADO);
  digitalWrite(ledPin, LOW);
}
