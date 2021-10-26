/*
 * IdleT.h
 *
 *  Created on: Jul 31, 2020
 *      Author: OS1
 */

#ifndef IDLET_H_
#define IDLET_H_

#include "Thread.h"

class IdleT : public Thread {
public:
	IdleT();
	~IdleT();

	void run();
	void start();

	PCB* myPCB;

};

#endif /* IDLET_H_ */
