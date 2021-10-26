/*
 * KernelEv.cpp
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "PCB.h"
#include "System.h"
#include "SCHEDULE.h"
#include "Queue.h"
#include "IVTEntry.h"
#include <stdio.h>

//Queue KernelEv::waitRed;

KernelEv::KernelEv(IVTNo ivtNo, Event* e) {
	// TODO Auto-generated constructor stub
	lock
	myNo=ivtNo;
	//ivtE=IVTEntry::dohvEntry(ivtNo);
	owner=PCB::running->myThread;
	val=0;
	IVTEntry::entry[myNo]->kEv=this;
	this->ev=e;
	waitRed=new Queue();
	unlock
}

KernelEv::~KernelEv() {
	// TODO Auto-generated destructor stub
	lock
	IVTEntry::entry[myNo]->kEv=0;
	owner=0;
	//ev=0;
	//delete ev;
	delete waitRed;
	unlock
}

void KernelEv::wait(){
	lock
	if(PCB::running->myThread!=owner){
		unlock
		return;
	}
	if(--val<0){
		waitRed->dodaj(PCB::running);
		PCB::running->stanje=PCB::BLOCKED;
		System::dispatch();
	}
	unlock
}

void KernelEv::signal(){
	lock
	if(val++<0){
		PCB* p=waitRed->dohvati();
		p->stanje=PCB::READY;
		Scheduler::put(p);
		waitRed->izbaci(p);
	}else{
		val=1;
	}
	unlock
}


