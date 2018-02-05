#ifndef smart_h
#define smart_h
#include "Arduino.h"

template <typename T>
class smart_ptr
{
  private:
	T *pData; 
  public:
	smart_ptr(T *pointer) :pData(pointer) {};
	~smart_ptr(){
		is_com("removing smart ptr data");
		delete pData;
	};
	T& operator *(){return *pData;};
	T* operator ->(){return pData;};
	void is_com(String msg){
		if(!Serial){
			return;
			}
		Serial.println(msg);
	};
	
	
	
};

class TestPtr
{
	public:
		TestPtr(String name){
			this->name=name;
		};
		String name;
};

#endif
