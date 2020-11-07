#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);
 
 int s=0; //Se definen variables
 int m=0;
 int inicio = 0;
volatile int st=0;
int Ast = 0;

void setup() 
{
lcd.begin(16,2);
lcd.backlight ();

attachInterrupt(digitalPinToInterrupt(2),ISR_Min,RISING);// Definimos los pines de interrupcion
attachInterrupt(digitalPinToInterrupt(3),ISR_S,RISING);
attachInterrupt(digitalPinToInterrupt(18),INICIA,RISING); 
attachInterrupt(digitalPinToInterrupt(19),REINICIA,RISING);
 pinMode(1,OUTPUT);
 lcd.setCursor(0,0);  //Se configura el cartel de inicio
 lcd.print("  Temporizador");
 lcd.setCursor(0,1);
 lcd.print("    Equipo 6");
 delay(1000);  //Despues de un tiempo predeterminado, el cartel cambia
 
 lcd.clear();
 lcd.setCursor(0,0); 
 lcd.print(" Elegir tiempo ");
 lcd.setCursor(5,1); 
 lcd.print("00:00");
 
}

void loop() 
{
  
  while((inicio%2) == 1) //Se inicia el ciclo, con esto, hacemos que 
  {                      //la cuenta regresiva inicie hasta que se presionado el botón de Inicio
    if(st>0){
    delay(500);
    st--;
    m = (st / 60) % 60;  //Convertimos los segundos totales en minutos
    s = st % 60;        //Convertimos los segundos totales en periodos de 60 segundos

    lcd.setCursor(0,0); 
    lcd.print("   Corriendo   ");
    
    lcd.setCursor(5,1);
    
    if(m<10)lcd.print("0");
    
    lcd.print(m);
    lcd.print(":");
    
    if(s<10) lcd.print("0");
    lcd.print(s);
    
    }
    if(st==0) {  //Cuando acabe el tiempo se cambia el cartel y se enciende el LED
    digitalWrite(1,HIGH);
    lcd.setCursor(0,0); 
    lcd.print("               ");
    lcd.setCursor(0,1); lcd.print("   Finalizado");
    delay (3000);
    lcd.clear();
    inicio = 0;
    }
  }

  while ((inicio%2) == 0){  //Se realiza la configuración para que pause o reinicie la cuenta.

    if (Ast > 0){
    st=0;
    Ast=0;
    }
 
    digitalWrite(1,LOW);
    delay(500);
    
    m = (st / 60) % 60;  //Convertimos los segundos totales en minutos
    s = st % 60;         //Convertimos los segundos totales en periodos de 60 segundos

    lcd.setCursor(0,0); 
    lcd.print(" Elegir tiempo ");
 
    lcd.setCursor(5,1);
    
    //lcd.setCursor(0,1);
    
    if(m<10)lcd.print("0");
    
    lcd.print(m);
    lcd.print(":");
    
    if(s<10) lcd.print("0");
    lcd.print(s);
  }
}
void ISR_Min()
{
  st=st+60;
  delay(200);
}

void ISR_S()
{
  st=st+1;
  delay(200);
}

void INICIA()
{
  inicio = inicio + 1;
}
void REINICIA()
{
Ast++;
inicio = 0;
}
