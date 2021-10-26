/*
 * PCB.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include "System.h"
#include "Queue.h"
#include "List.h"
#include "SCHEDULE.h"
#include <dos.h>
#include "stdio.h"

ID PCB::ids=0;
PCB* PCB::running;
List PCB::lista;

void PCB::wrapper(){
	PCB::running->myThread->run();
	PCB::running->stanje=PCB::OVER;
	//printf("OVER");
	lock
	PCB* temp=0;
	while(PCB::running->waitRed->vel>0){
		temp=PCB::running->waitRed->dohvati();
		temp->stanje=PCB::READY;
		Scheduler::put(temp);
		PCB::running->waitRed->izbaci(temp);
	}
	unlock
	System::dispatch();
}

void PCB::createStack(StackSize size){
	lock
	size=size/sizeof(unsigned int);
	stack=new unsigned int[size];
	stack[size-1]=0x200;
	stack[size-2]=FP_SEG(PCB::wrapper);
	stack[size-3]=FP_OFF(PCB::wrapper);
	ss=FP_SEG(stack+size-12);
	sp=FP_OFF(stack+size-12);
	bp=sp;
	unlock
}

PCB::PCB(StackSize stackS, Time timeSlice, Thread* myThread){
	lock
	this->myThread=myThread;
	stanje = NEW;
	myID=++ids;
	size=stackS;
	if(size>32768){
		size = 32768;
	}
	myTimeSlice=timeSlice;
	beskonacno=0;
	if(myTimeSlice==0){
		beskonacno=1;
	}
	waitRed=new Queue();
	createStack(size);
	lista.dodaj(this);
	zbogIstekaVremena=1;
	this->vremeCekanja=0;
	unlock
}

PCB::~PCB() {
	lock
	lista.izbaci(this);
	delete stack;
	delete waitRed;
	unlock
}






