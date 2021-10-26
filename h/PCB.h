/*
 * PCB.h
 *
 *  Created on: Jul 28, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"
class List;
class Queue;

class PCB {
public:
	Queue* waitRed;
	static List lista;
	static PCB* running;
	static ID ids;
	static void wrapper();

	int stanje;
	ID myID;
	Thread* myThread;
	unsigned int sp;
	unsigned int ss;
	unsigned int bp;
	Time myTimeSlice;
	unsigned int* stack;
	StackSize size;
	unsigned int vremeCekanja;
	int zbogIstekaVremena;
	int beskonacno;

	enum Stanje{NEW, READY, BLOCKED, OVER};

	PCB(StackSize stackS=defaultStackSize, Time timeSlice=defaultTimeSlice, Thread* myThread);
	~PCB();

	void createStack(StackSize size);


};

#endif /* PCB_H_ */
