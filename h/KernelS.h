/*
 * KernelS.h
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#ifndef KERNELS_H_
#define KERNELS_H_

#include "Queue.h"
#include "Semaphor.h"
class KernelL;

class KernelS {
public:
	KernelS(int init);
	~KernelS();

	int signal(int n=0);
	int wait(Time maxTimeToWait);
	int val();

	Queue* waitR;
	static KernelL allK;

	int value;

};

#endif /* KERNELS_H_ */
