/*
 * IVTEntry.h
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "Event.h"
#include "System.h"
#include <dos.h>
class KernelEv;
#include <stdio.h>




typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:
	IVTEntry(IVTNo i, pInterrupt p);
	~IVTEntry();

	static IVTEntry** entry;
	static IVTEntry* dohvEntry(IVTNo n);

	pInterrupt oldR,newR;
	KernelEv* kEv;
	IVTNo iv;
};

#define PREPAREENTRY(ivtNo, f)\
void interrupt INTERR##ivtNo(...);\
IVTEntry ENTRY##ivtNo(ivtNo,INTERR##ivtNo);\
void interrupt INTERR##ivtNo(...){\
	IVTEntry::entry[ivtNo]->kEv->signal();\
	if(f==1) IVTEntry::entry[ivtNo]->oldR();\
	System::dispatch();\
}


#endif /* IVTENTRY_H_ */
