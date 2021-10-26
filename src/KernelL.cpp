/*
 * KernelL.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include "KernelL.h"
#include "System.h"
#include <stdio.h>

KernelL::KernelL() {
	// TODO Auto-generated constructor stub
	lock
	prvi=posl=0;
	num=0;
	unlock

}

KernelL::~KernelL() {
	// TODO Auto-generated destructor stub
	lock
	while(prvi!=0){
		Elemm* stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
	prvi=posl=0;
	num=0;
	unlock
}

void KernelL::dodaj(KernelS* ks){
	lock
	Elemm* novi=new Elemm(ks);
	if(prvi==0)prvi=novi;
	else posl->sled=novi;
	posl=novi;
	num++;
	unlock
}

void KernelL::izbaci(KernelS* ks){
	lock
	Elemm* tek=prvi;
	Elemm* pret=0;
	if(tek==0){
		unlock
		return;
	}
	while(tek!=0 && tek->kern!=ks){
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
	num--;
	unlock
}

void KernelL::provera(){
	lock
	Elemm*tek=prvi;
	while(tek!=0){
		tek->kern->waitR->prodjiKrozListu();
		tek=tek->sled;
	}
	unlock
}

void KernelL::povecajValue(PCB* p){
	lock
	for(Elemm*pom=prvi;pom!=0;pom=pom->sled){
		if(pom->kern->waitR->daLiSadrzi(p)==1){
			pom->kern->value++;
		}
	}
	unlock
}

