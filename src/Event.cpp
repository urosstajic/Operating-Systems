/*
 * Event.cpp
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"
#include "System.h"

Event::Event(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	lock
	myImpl=new KernelEv(ivtNo,this);
	unlock
}

Event::~Event() {
	// TODO Auto-generated destructor stub
	//lock
	delete myImpl;
	//unlock
}

void Event::wait(){
	lock
	myImpl->wait();
	unlock
}

void Event::signal(){
	lock
	myImpl->signal();
	unlock
}

