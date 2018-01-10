//SisProV.ino
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
/*Definicion de pines*/
#define MagneticSensor 22
#define HitSensor 23
#define MovementSensorOne 24
#define MovementSensorTwo 25
#define CurtainOpening 26
/************************************/
/*Definicion de pines de activacion*/
#define RelayOne 27
#define RelayTwo 28
#define Electromagnet 29
#define Insurance 30
#define Buzzer 31
#define Alarm 32
/***********************************/
/*Variables auxiliares*/
bool estado = LOW;
unsigned long ReedTime;
unsigned long CurtainTime = 2000;
unsigned long OneSecond = 1000;
unsigned long ThreeSecond = 3000;
unsigned long currentMillis = 0;
unsigned long TimeUpdate = 0;
bool AuxBool = false;
bool stateReed = false;
/*Definicion de pines pantalla LCD*/
#define DB4 5
#define DB5 4
#define DB6 3
#define DB7 2
#define RS 12
#define EN 11
/************************************/
/*Definicion de indicadores LED's*/
#define LED1 53
#define LED2 52
#define LED3 51
#define LED4 50
/*************************************/
void ConfigInputs(){	
	pinMode(MagneticSensor, INPUT);
	pinMode(HitSensor, INPUT);
	pinMode(MovementSensorOne, INPUT);
	pinMode(MovementSensorTwo, INPUT);
	pinMode(CurtainOpening, INPUT);	
}
void ConfigOutputs()
{
	pinMode(RelayOne, OUTPUT);
	pinMode(RelayTwo, OUTPUT);
	pinMode(Electromagnet, OUTPUT);
	pinMode(Insurance, OUTPUT);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
}

void OpenCurtain()
{
	digitalWrite(Electromagnet, estado);
	digitalWrite(LED1, !estado);
	digitalWrite(LED2, estado);
}
void CloseCurtain()
{
	digitalWrite(Electromagnet, !estado);
	digitalWrite(Alarm, !estado);
	digitalWrite(LED1, estado);
	digitalWrite(LED2, !estado);
}
void HideGold()
{
	digitalWrite(RelayOne, estado);
	digitalWrite(RelayTwo, !estado);
	digitalWrite(Alarm, !estado);
	digitalWrite(LED3, !estado);
	digitalWrite(LED4, estado);
}
void SeeGold()
{
	digitalWrite(RelayOne, !estado);
	digitalWrite(RelayTwo, estado);
	digitalWrite(LED3, estado);
	digitalWrite(LED4, !estado);
}
void NormalState()
{
	OpenCurtain();
	SeeGold();
}
/*Inicializando display*/
LiquidCrystal display(RS, EN, DB4, DB5, DB6, DB7);
/**********************/
void setup() 
{
	ConfigInputs();
	ConfigOutputs();
	display.begin(16,2);
	for(int i=1; i>=0; i--)
	{
		display.print("Loading.");
		delay(400);
		display.clear();
		display.print("Loading..");
		delay(400);
		display.clear();
		display.print("Loading...");
		delay(400);
		display.clear();
	}
}

void loop() 
{
	display.clear();
	display.setCursor(0,0);
	display.print("Init SisProV");
	//currentMillis = millis();
	while(AuxBool == false)
	{
		delay(100);
		display.clear();
		display.setCursor(0,0);
		display.print("Normal State");
	    NormalState();
	    if(digitalRead(MagneticSensor) == estado)
		{
			delay(3000);
			if(digitalRead(MagneticSensor) == estado)
			{
				display.clear();
				display.setCursor(0,0);
				display.print("Safe Showcase");
				HideGold();
				CloseCurtain();
				AuxBool = true;
				break;
			}
		}
			}
	while(AuxBool == true)
	{
		delay(100);
		if(digitalRead(CurtainOpening) == estado)
		{
			delay(4000);
			if(digitalRead(CurtainOpening) == estado){
			    display.clear();
				display.setCursor(0,0);
				display.print("Abriendo Cortina");
				NormalState();
				AuxBool = false;
			break;
			} else {
			    // statement
			}
			
		} else {
	    
		}
	}
		
}




	/*else
	{
		if(digitalRead(CurtainOpening) == !estado)
		{
		AuxBool = false;
		display.clear();
		display.setCursor(0,0);
		display.print("Abriendo Cortina");
	    //display.setCursor(0,1);
		//currentMillis = millis();
		//display.print("Restaurando...");
		//OpenCurtain();
		//digitalWrite(Insurance, !estado);
		//if(millis() - currentMillis == ThreeSecond)
		//{
		//	display.print("Abrir Cortina");
		//	currentMillis = 0;
		//	digitalWrite(Insurance, estado);
		//}
		NormalState();
		} else {
	    
		}
	}*/
	
			
			//display.print("ReedSwitch ON");
			//currentMillis = millis();
			//if((millis() - currentMillis) >= CurtainTime)
			//if(currentMillis > TimeUpdate + CurtainTime)
			//{
			//	//TimeUpdate = currentMillis;
			//	display.setCursor(0,1);
			//	display.print("Protegiendo Vitrina");
			//	HideGold();
			//	CloseCurtain();
			//	AuxBool = HIGH;
			//	currentMillis = 0;
			//}
			//if(AuxBool == HIGH){
			//    display.print("Vitrina segura");
			//    AuxBool = LOW;
			//} else {
			//    
			//}
		//}else
		//{
			//display.clear();
			//display.setCursor(0,0);
			//display.print("SisProV ONLINE");
			//display.setCursor(0,1);
			//display.print("Estado normal");
			//NormalState();
		
		// if(stateReed)
		// {
		// 	display.clear();
		// 	display.setCursor(0,0);
		// 	display.print(millis());
		// 	display.setCursor(0,1);
		// 	display.print(currentMillis);
		// 	if((millis() - ReedTime) >= CurtainTime)
		// 	{
		// 		//TimeUpdate = currentMillis;
		// 		display.setCursor(0,1);
		// 		display.print("Safe Showcase");
		// 		HideGold();
		// 		CloseCurtain();
		// 		AuxBool = HIGH;
		// 		currentMillis = 0;
		// 		stateReed = false;
		// 	}
		// 	if(AuxBool == HIGH){
		// 	    display.print("Vitrina segura");
		// 	    AuxBool = LOW;
		// 	} else {
			    
		// 	}//

		// }else{
		// 	NormalState();
		// }






	/*if(digitalRead(HitSensor) == !estado)
	{
	    display.setCursor(0,1);
		currentMillis = millis();
		display.print("Volteando Charolas");
		HideGold();
		if(millis() - currentMillis == OneSecond)
		{
			display.print("Cerrando Cortina");
			currentMillis = 0;
		}
		CloseCurtain();
		currentMillis = millis();
		if(millis() - currentMillis == OneSecond)
		{
			display.print("Vitrina Protegida");
			currentMillis = 0;
		}
		}else {
		    
		}

	if(digitalRead(CurtainOpening) == estado)
	{
		AuxBool = false;
	    //display.setCursor(0,1);
		//currentMillis = millis();
		//display.print("Restaurando...");
		//OpenCurtain();
		//digitalWrite(Insurance, !estado);
		//if(millis() - currentMillis == ThreeSecond)
		//{
		//	display.print("Abrir Cortina");
		//	currentMillis = 0;
		//	digitalWrite(Insurance, estado);
		//}
		//NormalState();
	} else {
	    
	}*/
