/*
 * MainT.h
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#ifndef MAINT_H_
#define MAINT_H_

#include "Thread.h"

class MainT:public Thread {
public:
	MainT();
	//~MainT();

	PCB* myPCB;
};

#endif /* MAINT_H_ */
