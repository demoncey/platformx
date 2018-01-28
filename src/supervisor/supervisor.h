#ifndef supervisor_h
#define supervisor_h
#include "Arduino.h"
#include <SoftwareSerial.h> 
#include "../../src/utils/vector.h"
#include "task.h"

//class Task;

#define MAX_POOL 10

class Supervisor
{
	public:
		Supervisor(String name);
		void addTask(Task *task);
		void deleteTask(Task *task);
		void addTaskToChain(Task& task);
		void deleteTaskFromChain(Task& task);
		
		
		void run();
		void executeChain();
		void suspendChain();
		void resumeChain();
	private:
		String name;
		void is_com(String msg);
		size_t task_nb;
		Task *tasks[MAX_POOL];
		//task chain
		Task  *first,*current,*last;
		
		
};




#endif
