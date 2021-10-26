/*
 * Queue.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: OS1
 */

#include "Queue.h"
#include "PCB.h"
#include "System.h"
#include "SCHEDULE.h"
#include "KernelS.h"
#include "KernelL.h"
#include <iostream.h>
#include <stdio.h>

Queue::Queue() {
	// TODO Auto-generated constructor stub
	lock
	prvi=posl=0;
	vel=0;
	unlock
}

Queue::~Queue() {
	// TODO Auto-generated destructor stub
	lock
	while(prvi!=0){
		Elem* stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
	prvi=0;
	posl=0;
	vel=0;
	unlock
}


void Queue::dodaj(PCB* p){
	lock
	Elem* novi=new Elem(p);
	if(prvi==0)prvi=novi;
	else posl->sled=novi;
	posl=novi;
	vel++;
	unlock
}

void Queue::izbaci(PCB* p){
	lock
	Elem* tek=prvi;
	Elem* pret=0;
	if(tek==0){
		unlock
		return;
	}
	while(tek!=0 && tek->pcb!=p){
		pret=tek;
		tek=tek->sled;
	}
	if(tek==prvi)prvi=prvi->sled;
	else pret->sled=tek->sled;
	if(tek==posl){
		posl=pret;
	}
	tek->sled=0;
	delete tek;
	vel--;
	unlock
}

PCB* Queue::dohvati(){//dohvatam prvi
	lock
	if(prvi==0){
		unlock
		return 0;
	}
	//Elem*stari=prvi;
	//prvi=prvi->sled;
	//vel--;
	unlock
	return prvi->pcb;

}

void Queue::prodjiKrozListu(){//i smanji za 1 i izbaci taj elem iz liste ako je njegovo vreme cekanja doslo do 0 i postavi ga u red spremnih
	lock
	Elem*tek=prvi;
	while(tek!=0){
		if(tek->pcb->vremeCekanja!=0){
			tek->pcb->vremeCekanja--;
			if(tek->pcb->vremeCekanja==0){
				Elem*stari=tek;
				tek=tek->sled;
				stari->pcb->stanje=PCB::READY;
				stari->pcb->zbogIstekaVremena=0;
				Scheduler::put(stari->pcb);
				KernelS::allK.povecajValue(stari->pcb);
				izbaci(stari->pcb);
				continue;
			}
		}
		tek=tek->sled;
	}
	unlock
}

int Queue::daLiSadrzi(PCB* p){
	lock
	for(Elem*pom=prvi;pom!=0;pom=pom->sled){
		if(pom->pcb==p){
			unlock
			return 1;
		}
	}
	unlock
	return 0;
}


