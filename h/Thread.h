// File: thread.h
#ifndef _thread_h_
#define _thread_h_

class PCB;

typedef unsigned long StackSize;
const StackSize defaultStackSize = 1024;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class Thread {
public:
	friend class System;
	void start();
	void waitToComplete();
	virtual ~Thread();
	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);
protected:
 	 friend class PCB;
 	 Thread(StackSize stackSize=defaultStackSize, Time timeSlice=defaultTimeSlice);
 	 virtual void run();
private:
 	 PCB* myPCB;
};
void dispatch();
#endif
