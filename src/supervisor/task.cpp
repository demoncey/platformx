#include "Arduino.h"
#include "task.h"


Task::Task(Callback callback):suspended(false),task_callback(callback),priority(P_LOW){;}

Task::Task(Callback callback,bool suspend):suspended(suspend),task_callback(callback),priority(P_LOW){;}

Task::Task():suspended(false),priority(P_LOW){;}

void Task::execute(){
	task_callback();
}




