#include "Arduino.h"
#include "supervisor.h"


Supervisor::Supervisor(String name)
{
	this->name=name;
	first=NULL;
	current=NULL;
	last=NULL;
}


void Supervisor::addTask(Task& task){
	if(task.getSupervisor()==this){
		is_com("Supervisor: trying to add same task again, interuppted");
		return;
	}
	if( first==NULL){
		first=&task;
		task.before=NULL;
	}else{
		last->after=&task;
		task.before=last;
	}
	task.setSupervisor(this);
	task.after=NULL;
	last=&task;
}


void Supervisor::deleteTask(Task& task){
	is_com("Supervisor:task "+String(task.ptr_value,HEX)+" removed");
	if(&task==first){
		task.before=NULL;
		first=task.after;
		return;
	}
	if(&task==last){
		task.before->after=NULL;
		return;
	}
	task.before->after=task.after;
}


void Supervisor::execute(){
	current=first;
	while(current){
		if(current->isRunning()){
			current->execute();
			is_com("Supervisor:task "+String(current->ptr_value,HEX)+" executed in chain");
			//delay(1000);
		}else{
			is_com("Supervisor:task "+String(current->ptr_value,HEX)+" is suspend omitting execute");
		}
		current=current->after;
		delay(300);
	}
	is_com("Supervisor:Cycle finished, reseting");
	is_com("---------------------------------------------------------------------------------------");
	current=NULL;
}



void Supervisor::suspend(){
	current=first;
	while(current){
		if(current->isRunning() && current->priority!=P_IMMORTAL){
			current->suspend();
			is_com("Supervisor:task "+String(current->ptr_value,HEX)+" suspended");
		}
		current=current->after;
	}
	current=NULL;
}


void Supervisor::resume(){
	current=first;
	while(current){
		if(current->isRunning()==false){
			current->resume();
			is_com("Supervisor:task "+String(current->ptr_value,HEX)+" resumed");
		}
		current=current->after;
	}
	current=NULL;
	
}


void Supervisor::is_com(String msg){
		if(!Serial){return;}
		Serial.println(msg);
	}




