/*
 * Semaphor.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#include "Semaphor.h"
#include "KernelS.h"
#include "System.h"

Semaphor::Semaphor(int init) {
	// TODO Auto-generated constructor stub
	lock
	this->myImpl=new KernelS(init);
	unlock
}

Semaphor::~Semaphor() {
	// TODO Auto-generated destructor stub
	lock
	delete myImpl;
	unlock
}

int Semaphor::signal(int n){
	lock
	int ret=this->myImpl->signal(n);
	unlock
	return ret;
}

int Semaphor::val()const{
	return this->myImpl->val();
}

int Semaphor::wait(Time maxTimeToWait){
	lock
	int ret=this->myImpl->wait(maxTimeToWait);
	unlock
	return ret;
}
