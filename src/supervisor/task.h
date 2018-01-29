#ifndef task_h
#define task_h
#include "Arduino.h"


#define P_IMMORTAL 0
#define P_HIGH 1
#define P_MEDIUM 2
#define P_LOW 3


class Supervisor;

typedef  void (*Callback)();

class Task
{
	friend class Supervisor;//access to private Task  (before after) in Supervisor
	public:
		Task();
		Task(Callback callback);
		Task(Callback callback, bool suspend);
		~Task();
		void execute();
		bool isRunning(){return !suspended;};
		void suspend(){this->suspended=true;};
		void resume(){this->suspended=false;};
		void setPriority(int priority){this->priority=priority;};
		int getPriority(){return priority;};
		void kill(){};
		void setSupervisor(Supervisor *supervisor){this->supervisor=supervisor;};
		Supervisor* getSupervisor(){return supervisor;};
	private:
		Callback task_callback;
		bool suspended;
		Supervisor *supervisor;
		Task *before, *after;
		int priority;
		int ptr_value;
	
};
#endif
