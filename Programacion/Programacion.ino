//SisProV.ino
#include "LiquidCrystal.h"
#include "EEPROM.h"
/*Definicion de pines*/
#define MagneticSensor 22;
#define HitSensor 23;
#define MovementSensorOne 24;
#define MovementSensorTwo 25
#define CurtainOpening 26;
/************************************/
/*Definicion de pines de activacion*/
#define RelayOne 27;
#define RelayTwo 28;
#define Electromagnet 29;
#define Insurance 30;
/***********************************/
/*Variables auxiliares*/
#define entrada = INPUT;
#define salida = OUTPUT;
#define bool estado = LOW;
#define int CurtainTime =7000;
#define int currentMillis;
/*Definicion de pines pantalla LCD*/
#define DB4 40;
#define DB5 41;
#define DB6 42;
#define DB7 43;
#define RS 44;
#define EN 45;
/************************************/
/*Definicion de indicadores LED's*/
#define LED1 53;
#define LED2 52;
#define LED3 51;
#define LED4 50;
/*************************************/
#define ConfigInputs()
{
	try
	{
		pinMode(MagneticSensor, entrada);
		pinMode(HitSensor, entrada);
		pinMode(MovementSensorOne, entrada);
		pinMode(MovementSensorTwo, entrada);
		pinMode(CurtainOpening, entrada);	
	}catch(Exception e){
		Serial.println(Error, no se configuraron las entradas)
		display.setCursor(0,1);
		display.print("Error ConfigInputs");
	}
};
#define ConfigOutputs()
{
	try
	{
		pinMode(RelayOne, salida);
		pinMode(RelayTwo, salida);
		pinMode(Electromagnet, salida);
		pinMode(Insurance, salida);
		pinMode(LED1, salida);
		pinMode(LED2, salida);
		pinMode(LED3, salida);
		pinMode(LED4, salida);
	}catch(Exception e){
		Serial.println(Error, no se configuraron las salidas)
		display.setCursor(0,1);
		display.print("Error ConfigOutputs");
	}
		
};
#define OpenCurtain()
{
	try
	{
		currentMillis = millis();
		digitalWrite(Electromagnet, estado);
		digitalWrite(LED4, !estado);
		if((millis()-currentMillis) == CurtainTime)
		{
			digitalWrite(LED4, estado);
		}
		currentMillis = 0;
	}catch(Exception e){

	}
	

};
#define CloseCurtain()
	{
		digitalWrite(Electromagnet, !estado);
	};
#define HideGold()
	{
		digitalWrite(RelayOne, estado);
		digitalWrite(RelayTwo, !estado);
	};
#define SeeGold()
	{
		digitalWrite(RelayOne, !estado);
		digitalWrite(RelayTwo, estado);
	};
	LiquidCrystal display(RS, EN, DB4, DB5, DB6, DB7);
void setup() 
{
		ConfigInputs();
		ConfigOutputs();
		display.begin(16,2);
		display.print("INICIANDO SisProV...");
		display.setCursor(0,1);
}

void loop() 
{
		if(MagneticSensor==!estado)
		{

		}

}