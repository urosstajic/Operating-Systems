/*
 * List.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#include "List.h"
#include "System.h"
#include "PCB.h"

List::List() {
	// TODO Auto-generated constructor stub
	lock
	prvi=posl=0;
	num=0;
	unlock

}

List::~List() {
	// TODO Auto-generated destructor stub
	lock
	while(prvi!=0){
		ElemL* stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
	prvi=0;
	posl=0;
	num=0;
	unlock
}

void List::dodaj(PCB* p){
	lock
	ElemL* novi=new ElemL(p);
	if(prvi==0)prvi=novi;
	else posl->sled=novi;
	posl=novi;
	num++;
	unlock
}

void List::izbaci(PCB* p){
	lock
	ElemL* tek=prvi;
	ElemL* pret=0;
	while(p!=tek->pcb && tek!=0){
		pret=tek;
		tek=tek->sled;
	}
	if(tek==prvi)prvi=prvi->sled;
	else{
		pret->sled=tek->sled;
	}
	if(tek==posl)posl=pret;
	tek->sled=0;
	delete tek;
	num--;
	unlock
}

PCB* List::dohvPCB(ID id){
	lock
	for(ElemL* tek=prvi;tek!=0;tek=tek->sled){
		if(tek->pcb->myID==id){
			unlock
			return tek->pcb;
		}
	}
	unlock
	return 0;
}

