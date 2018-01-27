#ifndef blueTooth_h
#define blueTooth_h
#include "Arduino.h"
#include <SoftwareSerial.h> 
class Bluetooth
{
  public:
    Bluetooth(int rx,int tx,int read_led,int write_led,int delay_time);
    void init();
    void send(String msg);
	String recv();
  private:
	SoftwareSerial bluetooth;
	int interval;
	int read_led;
	int write_led;
};

#endif
