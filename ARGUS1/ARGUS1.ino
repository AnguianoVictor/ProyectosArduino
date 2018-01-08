/*LIBRERIAS*/
#include <SPI.h>
#include <Ethernet.h>
#include <utility/w5100.h>
#include <avr/pgmspace.h>
/********************/
/*Definición de puertos*/
#define th 22               
#define vitrina 23          
#define sirena 24       
#define auditoria 25    
#define vitrina_elect 28
#define mensaje1 26        
#define mensaje2 27         
#define sensor_sonido A0    
#define sensor_humo A1      
#define sensor_sirena A2    
#define sensor_vitrina A3   
/**********************/
/*Creacion de elementos para conectarse a red*/
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    
IPAddress dnServer(4, 2, 2, 2);                         
IPAddress gateway(192, 168, 1, 3);                      
IPAddress subnet(255, 255, 255, 0);
//IPAddress ip(10 , 2, 0, 30); //--Suc PO Cuautitlan--
//IPAddress ip(10, 1, 6, 30); //--Suc Queretaro--
//IPAddress ip(10, 1 , 10, 30); //--Suc Prados                   
//IPAddress ip(10, 1 ,0 ,30); //--Suc Abastos--
//IPAddress ip(10, 1, 2, 106); //--Suc Coacalco--
//IPAddress ip(10, 90, 23, 30); //--Suc Nicolas Romero 2
//IPAddress ip(10, 90, 6, 30); //--Suc Cuautitlán 2
//IPAddress ip(10, 90, 11, 30); //--Suc Lomas Verdes
IPAddress ip(192, 168, 1, 159); //Pruebas                        
EthernetServer server(80);                            
/********************************************/
/*Declaración de variables de estado y auxiliares*/
PROGMEM const float Sensibilidad=0.139;         
PROGMEM const float offset=0.100;        
float sensor1_trampa;
float sensor1_sirena;  
float sensor1_audio;
float sensor1_vitrina;            
/*******************************************/
/*Funcion de configuración*/
void setup()
{
    pinMode(4, OUTPUT);                                    
    digitalWrite(4, LOW);                                                                    
    Ethernet.begin(mac, ip, dnServer, gateway, subnet);  
    W5100.setRetransmissionTime(0x07D0);  //setRetransmissionTime sets the Wiznet's timeout period, where each unit is 100us, so 0x07D0 (decimal 2000) means 200ms.
    W5100.setRetransmissionCount(3);      //setRetransmissionCount sets the Wiznet's retry count. 
    server.begin();                                         //Inicializacion del puerto 80
    pinMode(th,OUTPUT);                                     //Se declara el pin de la trampa de humo como salida. 
    pinMode(vitrina,OUTPUT);                                //Se declara el pin de la vitrina como salida.
    pinMode(sirena,OUTPUT);                                 //Se declara el pin de la sirena como salida.
    pinMode(vitrina_elect,OUTPUT);                          //Se declara el pin de la vitrina de electronicos como salida.
    pinMode(auditoria, OUTPUT);
    pinMode(mensaje1,OUTPUT);                               //Se declara el pin del primer mensaje como salida.
    pinMode(mensaje2,OUTPUT);                               //Se declara el pin del segundo mensaje como salida.
    //pinMode(sensor_vitrina,INPUT);                          //Se declara el pin del sensor de la vitrina como entrada
    //pinMode(sensor_sonido,INPUT);                           //Se declara el pin del sensor del sistema de sonido como entrada
    //pinMode(sensor_humo,INPUT);                             //Se declara el pin del sensor de la trampa de humo como entrada
    //pinMode(sensor_sirena, INPUT);                          //Se declara el pin del sensor de la sirena como entrada
    digitalWrite(th,LOW);                                  //Se inicializa el pin de la trampa de humo en alto (1)
    digitalWrite(vitrina,LOW);                             //Se inicializa el pin de la vitrina de oro en alto (1)
    digitalWrite(sirena,LOW);                             
    digitalWrite(vitrina_elect,LOW);                       //Se inicializa el pin de la vitrina de electronicos en alto (1)
    digitalWrite(auditoria,LOW);
    digitalWrite(mensaje1,LOW);                             //Se inicializa el pin del primer mensaje en bajo (0)
    digitalWrite(mensaje2,LOW);                             //Se inicializa el pin del segundo mensaje en bajo (0)
}
/*************************/
void Trampa_HumoOFF()                                       //Funcion para desactivar la trampa de humo
{
  digitalWrite(th,LOW);                                      //Se escribe en el pin de la trampa de humo en alto (1)
}
void Trampa_HumoON()                                        //Funcion para activar la trampa de humo
{
  digitalWrite(th,HIGH);                                       //Se escribe el pin de la trampa de humo en bajo (0)
  delay(700);                                                 //Retardo de 700ms
  digitalWrite(th,LOW);                                      //Se escribe el pin de la trampa de humo en alto (1)
}
void VitrinaOFF()                                           //Funcion para desactivar la vitrina de oro. 
{
  digitalWrite(vitrina,LOW);                                 //Se escribe el pin de la vitrina de oro en alto (1) 
}
void VitrinaON()                                            //Funcion para activar la vitrina de oro. 
{
  digitalWrite(vitrina,HIGH);                                  //Se escribe el pin de la vitrina de oro en bajo (0)
}
void VitrinaElectOFF()                                      //Funcion para desactivar la vitrina de electronicos.
{
  digitalWrite(vitrina_elect,LOW);                           //Se escribe el pin de la vitrina de oro en alto (1)
}
void VitrinaElectON()                                       //Funcion para activar vitrina de electronicos
{
  digitalWrite(vitrina_elect,HIGH);                            //Se escribe el pin de la vitrina de electronicos en bajo (0)
}
void SirenaOFF()                                            //Funcion para desactivar la sirena
{
  digitalWrite(sirena,LOW);                                  //Se escribe el pin de la sirena en alto (1)
}
void SirenaON()                                             //Funcion para activar la sirena
{
  digitalWrite(sirena,HIGH);                                   //Se escribe el pin de la sirena en bajo (0)
}
void AuditoriaON()
{
  digitalWrite(auditoria,HIGH);
}
void AuditoriaOFF()
{
  digitalWrite(auditoria,LOW);
}
void TodosOFF()                                             //Funcion para apagar todos los dispositivos
{
    digitalWrite(th,LOW);                                    //Se escribe el pin de la trampa de humo en alto (1)
    digitalWrite(vitrina,LOW);                               //Se escribe el pin de la vitrina en alto (1)
    digitalWrite(sirena,LOW);                                //Se escribe el pin de la sirena alto (1)
    digitalWrite(vitrina_elect,LOW);                         //Se escribe el pin de la vitrina de electronicos en alto (1)
}
void TodosON()                                              //Funcion para activar todos los dispositivos. 
{
    digitalWrite(th,HIGH);                                     //Se escribe el pin de la trampa de humo en bajo (0)
    delay(500);                                               //Retardo de 500ms
    digitalWrite(th,LOW);                                    //Se escribe el pin de la trampa de humo en alto (1)
    digitalWrite(vitrina,HIGH);                                //Se escribe el pin de la vitrina de oro en bajo (0)
    digitalWrite(sirena,HIGH);                                 
    digitalWrite(vitrina_elect,HIGH);                          //Se escribe el pin de la vitrina de electronicos en bajo (0)
}
void VOZ1()                                                 //Funcion para activar el primer mensaje
{
    digitalWrite(mensaje1,HIGH);                              //Se escribe el pin del primer mensaje en alto (1)
    delay(500);                                               //Retardo de 500ms
    digitalWrite(mensaje1,LOW);                               //Se escribe el pin del primer mensaje en bajo (0)
    digitalWrite(mensaje2,LOW);                               //Se escribe el pin del segundo mensaje en bajo (0)
}
void VOZ2()                                                 //Funcion para activar el segundo mensaje
{
    digitalWrite(mensaje1,LOW);                               //Se escribe el pin del primer mensaje en bajo (0)
    digitalWrite(mensaje2,HIGH);                              //Se escribe el pin del segundo mensaje en alto (1)
    delay(500);                                               //Retardo de 500ms
    digitalWrite(mensaje2,LOW);                               //Se escribe el pin del segundo mensaje en bajo (0)
}
/*Funcion bucle*/
void loop()                                                 //Inicializacion del bucle
{ 
  EthernetClient cliente = server.available();              //Se crea un objeto tipo Ethernet
    if (cliente)                                              //Si hay un cliente para conectarse...
      {
        boolean currentLineIsBlank = true;                      //Se crea una variable tipo boolean
        String cadena="";                                       //Se crea una variable vacia tipo String
          while (cliente.connected()) {                           //Mientra el cliente este conectado
            if (cliente.available()) {                              //Si el cliente esta disponible
              char c = cliente.read();                                //Se lee lo que tiene el cliente y se almacena en una variable llamada "c"
              Serial.write(c);                                        //Se escribe en consola la variable "c"
              cadena.concat(c);                                       //Unimos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String
              int posicion=cadena.indexOf("LED=");                    //Guardamos la posición de la instancia "LED=" a la variable 'posicion'
                //**********VERIFICACION DE LAS INSTRUCCIONES**************//
                if(cadena.substring(posicion)=="LED=ONT")               
                  {
                    Trampa_HumoON();
                  }
                if(cadena.substring(posicion)=="LED=OFFT")
                  {
                    Trampa_HumoOFF();
                  }
                if(cadena.substring(posicion)=="LED=ONV")
                  {
                    VitrinaON();
                  }
                if(cadena.substring(posicion)=="LED=OFFV")
                  {
                    VitrinaOFF();
                  }
                if(cadena.substring(posicion)=="LED=ONS")
                  {
                    SirenaON();
                  }
                if(cadena.substring(posicion)=="LED=OFFS")
                  {
                    SirenaOFF();
                  }
                if(cadena.substring(posicion)=="LED=ONL")
                  {
                    VitrinaElectON();
                  }
                if(cadena.substring(posicion)=="LED=OFFL")
                  {
                    VitrinaElectOFF();  
                  }
                if(cadena.substring(posicion)=="LED=ONU")
                  {
                    AuditoriaON();
                  }
                if(cadena.substring(posicion)=="LED=OFFU")
                  {
                    AuditoriaOFF();
                  }
                if(cadena.substring(posicion)=="LED=ONALL")
                  {
                    TodosON();
                  }
                if(cadena.substring(posicion)=="LED=OFFALL")
                  {
                    TodosOFF();
                  }
                if(cadena.substring(posicion)=="LED=ONW")
                  {
                    VOZ1();
                  }
                if(cadena.substring(posicion)=="LED=ONX")
                  {
                    VOZ2();
                  }
                  //*******TERMINO DE LA VERIFICACION DE LAS INSTRUCCIONES*************//
                if (c == '\n' && currentLineIsBlank) //Si se recoje una linea vacia, se considera que termino de leer las instrucciones. 
                  {
                    cliente.println("HTTP/1.1 200 OK");           //Respuesta por parte del Arduino
                    cliente.println("Content-Type: text/html");
                    cliente.println(); 
                    cliente.println("<!DOCTYPE HTML>");
                    cliente.println("<html>");
                    cliente.println("<head>");
                    cliente.println("<title>");
                    cliente.println("</title>");
                    cliente.println("<body>");   
                    //if(get_corriente(A0)>=15)                //Si el sensor detecta corriente a traves del sistema de sonido....
                    //{
                      cliente.println("1");                      //Se envia un 1 como confirmacion de disponibilidad
                    //}
                    //else                                          //Si el sensor no detecta corriente...
                    //{
                      //cliente.println("0");                         //Se envia un 0; el sistema de sonido no esta disponible
                     // }
                   //if(get_corriente(A1)>=15 )                 //Si el sensor detecta corriente a traves de la trampa de humo....
                    //{
                      cliente.println("1");                         //Se envia un 1 como confirmacion de disponibilidad
                    //}
                    //else                                          //Si el sensor no detecta corriente...
                    //{
                      //cliente.println("0");                         //Se envia un 0; la trampa de humo no esta disponible
                      //}
                    //if(get_corriente(A2)>=13)                //Si el sensor detecta corriente a traves de la sirena...
                    //{
                      cliente.println("1");                         //Se envia un 1 como confirmacion de disponibilidad
                    //}
                    //else                                          //Si el sensor no detecta corriente...
                    //{
                      //cliente.println("0");                         //Se envia un 0; la sirena no esta disponible
                      //}
                    //if(get_corriente(A3)>=13)                //Si el sensor detecta corriente a traves de la vitrina de oro...
                    //{
                      cliente.println("1");                         //Se envia un 1 como confirmacion de disponibilidad
                    //}
                    //else                                          //Si el sensor no detecta corriente...
                    //{
                      //cliente.println("0");                         //Se envia un 0; la vitrina de oro no esta disponible...
                      //}
                      cliente.println("</body>");
                      cliente.println("</html>");
                    break;                                        //Se rompe la sentencia
                  }
                if (c == '\n') 
                  {
                    currentLineIsBlank = true;
                  }
                else if (c != '\r')
                  {
                    currentLineIsBlank = false;
                  }
              }
            }
            delay(1);
            cliente.stop();// Cierra la conexión
      }
}           

float get_corriente(int a)
{
  float voltajeSensor;
  float corriente=0;
  long tiempo=millis();
  float Imax=0;
  float Imin=0;
  voltajeSensor = analogRead(a) * (5.0 / 1023.0);//lectura del sensor
  corriente=0.9*corriente+0.1*((voltajeSensor-2.527)/Sensibilidad); //Ecuación  para obtener la corriente
  if(corriente>Imax)Imax=corriente;
  if(corriente<Imin)Imin=corriente;
  return(100*((Imax-Imin)/2)-offset);
}
/*************************************************/
