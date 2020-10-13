#define LED 13 //Declara el PIN 13 como LED
#define LEDI 12
//Llama las librerías
#include <LiquidCrystal.h>     
#include <TimerOne.h>    
//Variable para la interrupción
volatile long int seg=0;
volatile long int minu=0;
//Configuración del LCD
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2); //(RS, E, D4,D5, D6, D7)
 
void setup()
{
   pinMode(LEDI,OUTPUT);
   pinMode(LED,OUTPUT);          //LED como Saída
   lcd.begin(16, 2);            // Inicia el LCD 20x04 (columnas, filas)   
   lcd.setCursor(2, 0);         // Coloca el cursor en las coordenadas (2,0)   
   lcd.print("TIMER ARDUINO"); // Escribe no LCD   
  
   Timer1.initialize(1000000);      //Configura el TIMER en 1 Segundo
   Timer1.attachInterrupt(Temporizador) ; //Configura la interrupción del Timer 1
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  delay(2000);
}
//Función de la Interrupción cuando se ejecuta el TIMER
void Temporizador(void)
{
  //Incrementa el timer
  seg++;
  digitalWrite(LEDI,LOW);
  if(seg>59){
    seg=0;
    minu++;
       
  }
   if(minu>=1 && seg>=30){    
       digitalWrite(LEDI,HIGH);
       seg=0;
       minu=0;
    }
  //Muestra en el LCD el valor actual del temporizador
  lcd.setCursor(5, 1);
  lcd.print("    ");
  lcd.setCursor(5, 1);
  lcd.print(minu);
   lcd.setCursor(8, 1);
  lcd.print( ";");
  lcd.setCursor(10, 1);
  lcd.print("    ");
   lcd.setCursor(10, 1);
  lcd.print(seg);
}
