#ifndef supervisor_h
#define supervisor_h
#include "Arduino.h"
#include <SoftwareSerial.h> 
#include "../../src/utils/vector.h"
#include "task.h"


#define MAX_POOL 10

class Supervisor
{
	//friend class Task;
	public:
		Supervisor(String name);
		void addTask(Task& task);
		void deleteTask(Task& task);
		
		
		void run();
		void execute();
		void suspend();
		void resume();
	private:
		String name;
		void is_com(String msg);
		//task chain
		Task  *first,*current,*last;
		
		
};




#endif
