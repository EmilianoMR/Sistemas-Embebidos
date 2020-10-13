//Se crean las variables asociadas a cada LED
int LED0 = 22;
int LED1 = 23;
int LED2 = 24;
//Se crean las variables asociadas a cada Push Buttom 
int PULSADOR0 =18;
int PULSADOR1 =19;
int PULSADOR2 =20;
//Se crean las variables asociadas al estado incial de cada LED (Encendido)
volatile int estado0 = HIGH;
volatile int estado1 = HIGH;
volatile int estado2 = HIGH;

void setup(){
  //Se configuran los pines de los LEDS como salida
  pinMode (LED0, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  //Se configuran los pines de los Push Buttom como entrada
  pinMode (PULSADOR0, INPUT);
  pinMode (PULSADOR0, INPUT);
  pinMode (PULSADOR0, INPUT);
  //Se pone en estado incial a cada LED (Encendido) 
  digitalWrite (LED0, estado0);
  digitalWrite (LED1, estado1);
  digitalWrite (LED2, estado2);
  //Se configura la acción que sucederá cuanda haya una interrupción en cada pin de interrupción
  attachInterrupt (digitalPinToInterrupt(PULSADOR0), manejadorPulsador0, FALLING);
  attachInterrupt (digitalPinToInterrupt(PULSADOR1), manejadorPulsador1, FALLING);
  attachInterrupt (digitalPinToInterrupt(PULSADOR2), manejadorPulsador2, FALLING);
}

//Se generan funciones con la acción a realizar cuando se genere una interrupción, estas seran llamadas al haber una interrupción
void manejadorPulsador0(){
  estado0 = !estado0;
  dato0 = 1;
}
void manejadorPulsador1(){
  estado1 = !estado1;
}
void manejadorPulsador2(){
  estado2 = !estado2;
}

//En el loop se mantiene constantemente enviando el estado de los LED (Encendido/Apagado) a sus correspondientes pines
void loop (){
  digitalWrite(LED0, estado0);
  digitalWrite(LED1, estado1);
  digitalWrite(LED2, estado2);
}
