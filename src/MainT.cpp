/*
 * MainT.cpp
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#include "MainT.h"
#include "PCB.h"
#include "List.h"

MainT::MainT():Thread() {
	// TODO Auto-generated constructor stub
	myPCB=PCB::lista.dohvPCB(this->getId());
}

/*MainT::~MainT() {
	// TODO Auto-generated destructor stub
	delete myPCB;
}*/

