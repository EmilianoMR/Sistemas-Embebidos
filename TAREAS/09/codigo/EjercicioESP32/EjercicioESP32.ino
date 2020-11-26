//OCURRENCIA DE TAREAS
//Tareax: "---x"
//Tareay: "-----y"
//Tareaz: "-------z"

//ENVÍO DE DATOS ENTRE TAREAS
//Tarea x envió a y: "---x [-> y]"

//RECEPCIÓN DE DATOS ENTRE TAREAS
//Tarea x recibió de y: "---x [<- y]"

//SUSPENSIÓN DE TAREAS
//"---x [!]"

//AUMENTO DE PRIORIDAD EN TAREAS
//"---x [+]"

//==============================================================================
#include <Arduino.h>           //Librearía de arduino para ESP32

#define INCLUDE_vTaskSuspend 1 //Para activar la suspensión de tareas

QueueHandle_t coladetareas;    //Declaración de una cola para comunicación entre 
                               //tareas
int estadoled = 0;             //Variable que muestra el estado del LED

int a = 0;                     //Variable para funcionamiento de impresiones

//---------------------
//-----[ AJUSTES ]-----
//---------------------
void setup() {
  
//Creación de una cola de comunicación entre tareas
  coladetareas = xQueueCreate(10,         // Número de elementos de la cola
                              sizeof(int) // Tamaño de cada dato de la cola
                              );

  if (coladetareas != NULL) {  //Comprobación de que se ha creado la cola
    Serial.begin(115200);      //Se inicializa el puerto serie a 115200 baudios
    Serial.println("-- INICIO --");       //Se imprime una señal de inicio
    delay(1000);               //Delay de inicio de programa
    
// Creación de las tareas:
    xTaskCreate(
    Tarea1,                    // Función que ejecuta la tarea
    "Tarea1",                  // Cadena con el nombre de la tarea
    1000,                      // Tamaño del "Stack"
    NULL,                      // Parámetro pasado como entrada
    7,                         // Prioridad d la tarea
    NULL);                     // Manejador (Handle) de la tarea
    xTaskCreate(Tarea2, "Tarea2", 1000, NULL, 6, NULL);
    xTaskCreate(Tarea3, "Tarea3", 1000, NULL, 5, NULL);
    xTaskCreate(Tarea4, "Tarea4", 1000, NULL, 4, NULL);
    xTaskCreate(Tarea5, "Tarea5", 1000, NULL, 3, NULL);
    xTaskCreate(Tarea6, "Tarea6", 1000, NULL, 2, NULL);
    xTaskCreate(Tarea7, "Tarea7", 1000, NULL, 1, NULL);
    xTaskCreate(Tarea8, "Tarea8", 1000, NULL, 0, NULL);
  }
}

//-----------------------
//-----[ PRINCIPAL ]-----
//-----------------------
void loop() {}

//==============================================================================

//---------------------
//-----[ TAREA 1 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea1( void * parameter ){
    for( int i = 0;i<6;i++ ){         // Número de veces que ocurre esta tarea
        Serial.println("--- 01");     // Evidencia de ocurrencia
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 01");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 2 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea2( void * parameter){
    for( int i = 0;i<10;i++ ){        // Número de veces que ocurre esta tarea
        Serial.println("----- 02");   // Evidencia de ocurrencia
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 02");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 3 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea3( void * parameter){
    for( int i = 0;i<10;i++ ){        // Número de veces que ocurre esta tarea
        if(i == 4){                   //Suceso a la 5ta ejecución
          estadoled = 1;              //Ajusta el LED en ON
          
          //Envío de un dato a la cola de comunicación para su recepción
          xQueueSend(coladetareas, &estadoled, portMAX_DELAY);
          //Confirmación al usuario de que se ha enviado el dato
          Serial.println ("------- 03 [-> 4]");//Tarea 3 envía a 4
          
        }
        else{
          Serial.println("------- 03 ");// Evidencia de ocurrencia
        }
        
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 03");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 4 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea4( void * parameter){
    
    for( int i = 0;i<12;i++ ){        // Número de veces que ocurre esta tarea
      
      int valor = 0;                  //Contiene el estado del LED
      
            //Recepción de un dato de la cola de comunicación solo si hay datos
          if(xQueueReceive(coladetareas, &valor, 0) == pdPASS){
            //Confirmación al usuario de que se ha recibido el dato
            Serial.println ("--------- 04 [<- 3]"); //Tarea 4 recibe de 3
            
          }
          else{
            Serial.println("--------- 04");// Evidencia de ocurrencia
          }

        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 04");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 5 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea5( void * parameter){
    for( int i = 0;i<13;i++ ){        // Número de veces que ocurre esta tarea
        Serial.println("----------- 05");// Evidencia de ocurrencia
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 05");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 6 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea6( void * parameter){
    for( int i = 0;i<10;i++ ){        // Número de veces que ocurre esta tarea
      
        if( i > 5){                   //Ocurrencia a la 6ta ejecución
          vTaskPrioritySet( NULL, 7 );//Cambio de prioridad a la tarea
          a=a+1;
          if(a > 1){                  //Espera al cambio de prioridad ya que 
                                      //tarda una vuelta más
            Serial.println("------------- 06"); //Se muestra al usuario la nueva prioridad
          }else{
            Serial.println("------------- 06 [+]");//Ha cambiado de prioridad
          }
        }else{
          Serial.println("------------- 06"); // Evidencia de ocurrencia
        }
        
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 06");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 7 ]-----               
//---------------------
//------------------------------------------------------------------------------
void Tarea7( void * parameter){
    for( int i = 0;i<10;i++ ){        // Número de veces que ocurre esta tarea
        if(i > 4){
          Serial.println("--------------- 07 [!]"); //Tarea suspendida
          vTaskSuspend (NULL);        //Suspensión anticipada de la tarea
        }else{
          Serial.println("--------------- 07");// Evidencia de ocurrencia
        }
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 07");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 8 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea8( void * parameter){
    for( int i = 0;i<13;i++ ){        // Número de veces que ocurre esta tarea
        Serial.println("----------------- 08");// Evidencia de ocurrencia
        Serial.println("");
        vTaskDelay(2000);             // Espera...
    }
    Serial.println("--> 08");         // Conclusión de la tarea
    vTaskDelete( NULL );              // Se "Borra"
}
//******************************************************************************
