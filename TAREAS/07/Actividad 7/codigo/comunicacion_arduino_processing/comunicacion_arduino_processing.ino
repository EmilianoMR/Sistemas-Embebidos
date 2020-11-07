const int Trigger = 53;   //Pin digital 2 para el Trigger del sensor
const int Echo = 52;   //Pin digital 3 para el echo del sensor
int led = 51;

int t = 0;
int d = 0;


void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  pinMode(led, OUTPUT);
}


void loop() {
  if (Serial.available()) {
    char en = Serial.read();
    if (en == 'e') {
      digitalWrite(led, 1);
    }
    else if (en == 'a')
      digitalWrite(led, 0);
  }
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t / 59;           //escalamos el tiempo a una distancia en cm



  Serial.write(d);      //Enviamos serialmente el valor de la distancia
  delay(100);          //Hacemos una pausa de 100ms

}
