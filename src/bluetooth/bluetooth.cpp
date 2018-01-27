#include "Arduino.h"
#include "bluetooth.h"
#include <SoftwareSerial.h> 
Bluetooth::Bluetooth(int rx,int tx,int read_led,int write_led,int delay_time):bluetooth(SoftwareSerial(rx,tx))
{
  
  this->interval=delay_time;
  this->write_led=read_led;
  this->read_led=write_led;
  
}

void Bluetooth::init()
{
	bluetooth.begin(38400);
}


void Bluetooth::send(String msg)
{
	digitalWrite(write_led,HIGH);
	bluetooth.println(msg);
	delay(interval);
	digitalWrite(write_led,LOW);
}

String Bluetooth::recv()
{
	String recived="";
	bool switch_on=true;
	while(bluetooth.available()>0){
		if(switch_on){
			digitalWrite(read_led,HIGH);
			switch_on=false;
			delay(interval);
		}
		char c = bluetooth.read();
		recived+=c;
	}
	digitalWrite(read_led,LOW);
	return recived;
}
