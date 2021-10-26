/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <dos.h>
#include "System.h"

IVTEntry** IVTEntry::entry=new IVTEntry*[256];

IVTEntry::IVTEntry(IVTNo i, pInterrupt p) {
	// TODO Auto-generated constructor stub
	lock
	//IVTEntry* IVTEntry::entry={0};
	if(i>=0 && i<=255){
		this->iv=i;
	}
	this->oldR=getvect(i);
	newR=p;
	setvect(i,newR);
	entry[i]=this;
	unlock

}

IVTEntry::~IVTEntry() {
	// TODO Auto-generated destructor stub
	lock
	oldR();
	setvect(iv,oldR);
	entry[iv]=0;
	unlock
}

IVTEntry* IVTEntry::dohvEntry(IVTNo n){
	lock
	IVTEntry* e=entry[n];
	unlock
	return e;
}


