#ifndef task_h
#define task_h
#include "Arduino.h"
//#include "supervisor.h"


class Supervisor;

typedef  void (*Callback)();
class Task
{
	friend class Supervisor;
	public:
		Task();
		Task(Callback callback);
		Task(Callback callback, bool suspend);
		~Task(){};
		void execute();
		bool isRunning(){return !suspended;};
		void suspend(){this->suspended=true;};
		void resume(){this->suspended=false;};
		void kill(){};
		void setSupervisor(Supervisor *supervisor){this->supervisor=supervisor;};
		Supervisor* getSupervisor(){return supervisor;};
	private:
		Callback task_callback;
		bool suspended;
		Supervisor *supervisor;
		Task *before, *after;
	
};
#endif
