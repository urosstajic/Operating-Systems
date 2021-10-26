/*
 * KernelEv.h
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "Event.h"
//#include "IVTEntry.h"
#include "Queue.h"
#include "Thread.h"

class IVTEntry;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo, Event* e);
	~KernelEv();

	void wait();
	void signal();

	Queue* waitRed;

private:
	//IVTEntry* ivtE;
	IVTNo myNo;
	Thread* owner;
	int val;
	Event* ev;
};

#endif /* KERNELEV_H_ */
