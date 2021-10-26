/*
 * KernelS.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#include "KernelS.h"
#include "System.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "KernelL.h"
#include "IdleT.h"
#include "MainT.h"
#include <stdio.h>

//BlockedL KernelS::waiting;
KernelL KernelS::allK;

KernelS::KernelS(int init) {
	// TODO Auto-generated constructor stub
	lock
	value=init;
	allK.dodaj(this);
	waitR=new Queue();
	unlock
}

KernelS::~KernelS(){
	lock
	delete waitR;
	unlock
}

int KernelS::val(){
	return value;
}

int KernelS::signal(int n){
	lock
	if(n<0){
		unlock
		return n;
	}
	else if(n==0){
		if(value++<0){
			PCB* p=waitR->dohvati();
			p->stanje=PCB::READY;
			p->zbogIstekaVremena=1;
			Scheduler::put(p);
			waitR->izbaci(p);
		}
		unlock
		return 0;
	}
	else if(n>0){
		if(n>waitR->vel){
			int ret=0;
			for(int i=0;i<waitR->vel;i++){
				PCB* p=waitR->dohvati();
				p->stanje=PCB::READY;
				p->zbogIstekaVremena=1;
				Scheduler::put(p);
				waitR->izbaci(p);
				ret++;
			}
			value+=n;
			unlock
			return ret;
		}else{
			int ret=0;
			for(int i=0;i<n;i++){
				PCB* p=waitR->dohvati();
				p->stanje=PCB::READY;
				p->zbogIstekaVremena=1;
				Scheduler::put(p);
				waitR->izbaci(p);
				ret++;
			}
			value+=n;
			unlock
			return ret;
		}
	}
}

int KernelS::wait(Time maxTimeToWait){
	lock
	//printf("usao u wait\n");
	//printf("Pozvala ThreadID %d\n", PCB::running->myID);
	value--;
	if(value<0){
		//if(PCB::running!=System::idle->myPCB){
			PCB::running->stanje=PCB::BLOCKED;
			waitR->dodaj(PCB::running);
			if(maxTimeToWait!=0){
				PCB::running->vremeCekanja=maxTimeToWait;
			}else{
				PCB::running->vremeCekanja=0;
			}
			System::dispatch();
	//	}
	}
	if(PCB::running->zbogIstekaVremena==0){
		PCB::running->zbogIstekaVremena=1;
		unlock
		return 0;
	}else{
		//PCB::running->zbogIstekaVremena=0;
		unlock
		return 1;
	}
}


