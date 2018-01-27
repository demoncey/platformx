#include "Arduino.h"
#include "com.h"
#include <SoftwareSerial.h> 
Com::Com(int delay_time)
{
  this->interval=delay_time;
}

void Com::init()
{
	Serial.begin(9600);
    while (!Serial) {
    ; 
  }
}


void Com::send(String msg)
{
	Serial.println(msg);
}

String Com::recv()
{
	String recived="";
	while(Serial.available()>0){
		char c = Serial.read();
		recived+=c;
	}
	return recived;
}
