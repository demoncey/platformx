#include "Arduino.h"
#include "supervisor.h"
#include "../../src/utils/vector.h"


Supervisor::Supervisor(String name):task_nb(0)
{
	this->name=name;
	//tasks=new Task[10];
	first=NULL;
	current=NULL;
	last=NULL;
}


void Supervisor::addTaskToChain(Task& task){
	if( first==NULL){
		first=&task;
		task.before=NULL;
	}else{
		last->after=&task;
		task.before=last;
	}
	task.after=NULL;
	last=&task;
}

void Supervisor::addTask(Task *task){
	if(task_nb>MAX_POOL){
		return;
	}
	if(task->getSupervisor()==this){
		is_com("Supervisor: trying to add same task again, interuppted");
		return;
	}
	task->setSupervisor(this);
	tasks[task_nb++]=task;
	is_com("Supervisor: task added");
}

void Supervisor::deleteTask(Task *task){
	;
}

void Supervisor::run()
{
	for( int idx = 0; idx < task_nb; ++idx ){
		if(tasks[idx]->isRunning()){
				tasks[idx]->execute();
				is_com("Supervisor:task "+String(idx)+" executed");
		}else{
			is_com("Supervisor:task "+String(idx)+" suspended");
		}
		delay(300);
	}
}


void Supervisor::executeChain(){
	current=first;
	while(current){
		if(current->isRunning()){
			current->execute();
			is_com("Supervisor:task executed in chain");
			delay(300);
		}
		current=current->after;
	}
}



void Supervisor::suspendChain(){
	
}


void Supervisor::resumeChain(){
	
}


void Supervisor::is_com(String msg){
		if(!Serial){return;}
		Serial.println(msg);
	}




