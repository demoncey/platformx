#ifndef com_h
#define com_h
#include "Arduino.h"
class Com
{
  public:
    Com(int delay_time);
    void init();
    void send(String msg);
	String recv();
  private:
	int interval;
};

#endif
