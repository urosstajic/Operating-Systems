/*
 * Thread.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: OS1
 */
#include <iostream.h>
#include "Thread.h"
#include "System.h"
#include "SCHEDULE.h"
#include "PCB.h"
#include "List.h"
#include "Queue.h"
#include "stdio.h"


Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(stackSize,timeSlice,this);
}

Thread::~Thread(){
	lock
	//cout<<"Deleting thread with ID "<< myPCB->myID << endl;
	waitToComplete();
	delete myPCB;
	unlock
}

void Thread::start(){
	lock
	myPCB->stanje = PCB::READY;
	Scheduler::put(myPCB);
	unlock
}

ID Thread::getRunningId(){
	lock
	ID id=PCB::running->myID;
	unlock
	return id;
}

ID Thread::getId(){
	lock
	ID id=myPCB->myID;
	unlock
	return id;
}

void Thread::waitToComplete(){
	lock
	//printf("WAIT TO COMPLETE");
	if (this==PCB::running->myThread || this==System::starting || this==System::idle) {
		unlock
		return;
	}
	if(myPCB->stanje==PCB::OVER || myPCB->stanje==PCB::NEW) {
		unlock
		return;
	}
	//printf("WAIT TO COMPLETE");
	PCB::running->stanje = PCB::BLOCKED;
	myPCB->waitRed->dodaj(PCB::running);
	System::dispatch();
	unlock
}

Thread* Thread::getThreadById(ID id){
	lock
	PCB* p=PCB::lista.dohvPCB(id);
	unlock
	return p->myThread;
}

void dispatch(){
	//lock
	System::dispatch();
	//unlock
}

void Thread::run(){}

