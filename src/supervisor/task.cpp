#include "Arduino.h"
#include "task.h"


Task::Task(Callback callback):suspended(false),task_callback(callback){;}

Task::Task(Callback callback,bool suspend):suspended(suspend),task_callback(callback){;}

Task::Task():suspended(false){;}

void Task::execute(){
	task_callback();
}




