/*
 * Semaphor.h
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

class KernelS;

typedef unsigned int Time;
class KernelSem;
class Semaphor {
public:
	Semaphor(int init=1);
	virtual ~Semaphor();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int n=0);
	int val () const; // Returns the current value of the semaphore
private:
	KernelS* myImpl;
};

#endif /* SEMAPHOR_H_ */
