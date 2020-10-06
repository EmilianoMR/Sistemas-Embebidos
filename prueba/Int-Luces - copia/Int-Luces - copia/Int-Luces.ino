//******************************************************************************
// Ejemplo del uso de Atención a Interrupciones
//
// Interrupciones asociadas a entradas de señales digitales
//
//******************************************************************************
// ---[ BIBLIOTECAS ]---
// De momento no se necesitan
// ---[ VARIABLES para ATENDER INTERRUPCIONES ]---
// Estas variables son GLOBALES, no deben ser alteradas por funciones ajenas
// a las "ISRs" o "CallBacks", al ser 'volatile', mantiene su valor entre
// ocurrencias de atenciones a las interrupciones.
volatile int velocidad = 20;
// ---[ VARIABLES ]---
const int maxima = 1000;  // Valor máxima de cambio de velocidad parpadeo
const int minima = 20;    // Valor mínimo de cambio de velocidad parpadeo
const int aumenta = 20;   // Tasa de incremento en la velocidad
// ---[ ELEMENTOS de HARDWARE ]---
int leds[5] = {8, 9, 10, 11, 12}; // Arreglo de pines en donde están LEDs
//------------------------------------------------------------------------------
// ---[ AJUSTE PRINCIPAL ]---
//------------------------------------------------------------------------------
void setup() {

  for (int i = 0; i < 5; i++) { // Inicio de Índice ("i"), límite e incremento
    pinMode(leds[i], OUTPUT);   // Ajusta TODOS los LEDs como SALIDAS
    digitalWrite(leds[i], LOW); // y ahora con valores LOW
  }
  velocidad = minima;           // Ajuste velocidad con que se inicia

  // Ajuste pines que ORIGINAN INTERRUPCIONES, cambios de "Bajo" a "alto"
  attachInterrupt(digitalPinToInterrupt(2), velocidadMenos, RISING);
  attachInterrupt(digitalPinToInterrupt(3), velocidadMas, RISING);
}
//------------------------------------------------------------------------------
// -- -[ LAZO PRINCIPAL ]-- -
//------------------------------------------------------------------------------
void loop() {
  for (int i = 0; i < 5; i++) {       // Corrimiento de Izquierda a Derecha

    if (i > 0) {                      // Límite, precaución de no alcanzarlo
      digitalWrite(leds[i - 1], LOW); // Apagado del LED izquierdo
    }
    digitalWrite(leds[i], HIGH);      // Encendido del LED actual
    delay(velocidad);                 // Espera por el tiempo establecido
  }
  digitalWrite(leds[4], LOW);         //  Apagado del último LED
  //- - - - - - - - - - - - - - -
  for (int i = 4; i >= 0; i--) {      // Ahora, corrimiento de derecha a izquierda
    if (i < 4) {                      // Cuidado de no salirse del rango.
      digitalWrite(leds[i + 1], LOW); // Apagado del LED de la dercha
    }
    digitalWrite(leds[i], HIGH);      // Encendido del LED actual
    delay(velocidad);                 // Espera por el tiempo establecido
  }
  digitalWrite(leds[0], LOW);         //  Apagado del último LED
}
//------------------------------------------------------------------------------
//******************************************************************************
// ISR pin 2 --> Esta INTERRUPCIÓN disminuye la velocidad
//******************************************************************************
void velocidadMenos() {
  velocidad = velocidad - aumenta;
  if (velocidad < minima) {       // Verificar si se llegó al tope
    velocidad = minima;
  }
}
//******************************************************************************
// ISR pin 3 --> Esta INTERRUPCIÓN aumenta la velocidad
//******************************************************************************
void velocidadMas() {
  velocidad = velocidad + aumenta;
  if (velocidad > maxima) {     // Verificar si se llegó al tope
      velocidad = maxima;
    }
  }
//==============================================================================
