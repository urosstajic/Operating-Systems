/*
 * IdleT.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: OS1
 */

#include "IdleT.h"
#include "System.h"
#include "PCB.h"
#include "List.h"
#include <stdio.h>

IdleT::IdleT():Thread(defaultStackSize,1) {
	// TODO Auto-generated constructor stub
	//myPCB=new PCB(defaultStackSize,defaultTimeSlice,this);
	myPCB=PCB::lista.dohvPCB(this->getId());
	//this->myPCB=PCB::lista->dohvPCB(this->getId());
}

IdleT::~IdleT() {
	// TODO Auto-generated destructor stub
	//lock
	delete myPCB;
	//unlock
}

void IdleT::start(){
	lock
	this->myPCB->stanje = PCB::READY;
	unlock
}

void IdleT::run(){
	while(1){
		//cout<<"beskonacno    ";
		//printf("Radi idle");
	}
}
