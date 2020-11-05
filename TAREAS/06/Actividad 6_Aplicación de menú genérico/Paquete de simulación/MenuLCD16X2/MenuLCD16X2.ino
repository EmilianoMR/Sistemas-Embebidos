  #include <LiquidCrystal.h>    //Funciones del LCD
#include <Wire.h>

const byte NumMenuP = 5;
const byte NumMaxSubM = 4;

//Contantes para identificar las teclas
#define btnDERECHA      0
#define btnARRIBA      1
#define btnABAJO       2
#define btnIZQUIERDA   3
#define btnSELECT      4
#define btnNADA        5

//Indica a la librería los pines de conexión del shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

//Varables para leer las teclas y el ADC

int adc_key_in  = 0; 
int c =0;

//Función que lee las teclas 
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Leer la entrada analógica

 //Las teclas se conectan a un divisor resistivo que produce distintos valores de tensión según la tecla pulsada
 
 if (adc_key_in > 1000) return btnNADA; //Si no hay ninguna tecla pulsada, sale para demorar menos tiempo

 if (adc_key_in < 50)   return btnDERECHA;  
 if (adc_key_in < 195)  return btnARRIBA; 
 if (adc_key_in < 380)  return btnABAJO; 
 if (adc_key_in < 555)  return btnIZQUIERDA; 
 if (adc_key_in < 790)  return btnSELECT;   

 return btnNADA;  // No debería llegar aquí, pero por las dudas retorna este valor.
}
String MenuP[NumMenuP] = {
  "Item 1",
  "Item 2",
  "Item 3",
  "Item 4",
  "Item 5"
};
String SubMenus[NumMenuP][NumMaxSubM] = {
  {"LED ON","LED OFF","Sub item 1.3","Sub item 1.4"},
  {"Sub item 2.1","Sub item 2.2","Sub item 2.3","Sub item 2.4"},
  {"Sub item 3.1","Sub item 3.2","Sub item 3.3","Sub item 3.4"},
  {"Sub item 4.1","Sub item 4.2","Sub item 4.3","Sub item 4.4"},
  {"Sub item 5.1","Sub item 5.2","Sub item 5.3","Sub item 5.4"}
};

int lcd_key = -1;
int teclaAnt = -1;
boolean cursorAct = false;
unsigned long tiempo;
int x = -1;
int y = 0;
int LED = 3;

void setup() {
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("*Menu Arduino*");
  lcd.setCursor(3,1);
  lcd.print("Equipo 6");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Menu Principal");
  lcd.setCursor(0,1);
  lcd.print("Presione Select");
  tiempo = millis();
  
}

void loop() {  
   
  

  lcd_key = read_LCD_buttons();
  if(lcd_key==4 || c!=0){
  c++;
  if(lcd_key != teclaAnt){
  
    delay(50);
     lcd_key = read_LCD_buttons();
    if(lcd_key != teclaAnt){
      tiempo = millis();
      teclaAnt = lcd_key;
     
        
      if(lcd_key == 2){ //DOWN
        x++;
        y = 0;
        if(x > NumMenuP - 1) x = NumMenuP - 1;
      }

      if(lcd_key == 1){ //UP
        x--;
        if( x < 0) x = 0;
        y = 0;
        Serial.println(x);
      }

      if(lcd_key == 0){ //RIGTH
        y++;
        if( y > NumMaxSubM - 1) y = NumMaxSubM - 1;
      }

      if(lcd_key == 3){ //LEFT
        y--;
        if(y < 0) y = 0;
      }

      if(lcd_key == 4){//SELECT
        if(x == 0 && y == 0){
          digitalWrite(LED, HIGH);
        } else if (x == 0 && y == 1){
          digitalWrite(LED, LOW);
        }

      }

      lcd.clear();
      lcd.print(MenuP[x]);
      lcd.setCursor(0,1); 
      lcd.print(SubMenus[x][y]);
    }
  }
  delay(50);
}
}
