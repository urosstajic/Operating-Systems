/*
 * List.h
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include "Thread.h"
class PCB;

class List {
private:
	struct ElemL{
		ElemL*sled;
		PCB* pcb;
		ElemL(PCB* p){
			pcb=p;
			sled=0;
		}
	};
	ElemL* prvi,*posl;

public:
	List();
	virtual ~List();
	void dodaj(PCB* p);
	void izbaci(PCB* p);
	PCB* dohvPCB(ID id);
	int num;
};

#endif /* LIST_H_ */
