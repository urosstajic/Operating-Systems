/*
 * System.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: OS1
 */

#include <stdlib.h>
#include <iostream.h>
#include <dos.h>
#include "System.h"
#include "IdleT.h"
#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "KernelS.h"
#include "KernelL.h"
#include "MainT.h"
#include <stdio.h>

MainT* System::starting;
IdleT* System::idle;
volatile int naZahtev=0;
extern void tick();
volatile unsigned int cnt;
volatile unsigned int tsp, tss,tbp;
unsigned oldTimerOFF, oldTimerSEG;


void interrupt timer(...){
	//printf("Usao u timeeer\n");
	if(naZahtev==0){
		//printf("**** proslo 55ms ****\n");
		tick();
		cnt--;
		//printf("cnt== %d\n",cnt);
		//if(PCB::running!=System::idle->myPCB)
		KernelS::allK.provera();
	}
	if(naZahtev || (cnt==0 && PCB::running->beskonacno==0)){
		asm{
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		PCB::running->sp=tsp;
		PCB::running->ss=tss;
		PCB::running->bp = tbp;
		if(PCB::running->stanje==PCB::READY && PCB::running!=System::idle->myPCB){
			Scheduler::put(PCB::running);
		}
		PCB::running=Scheduler::get();
		if(PCB::running==0){
			PCB::running=System::idle->myPCB;
		}
		tsp=PCB::running->sp;
		tss=PCB::running->ss;
		tbp = PCB::running->bp;
		cnt=PCB::running->myTimeSlice;

		asm{
			mov sp, tsp
			mov ss,tss
			mov bp,tbp
		}
	}
	if(!naZahtev){
		asm int 60h
	}
	naZahtev=0;
}

void System::pocetak(){
	idle=new IdleT();
	cnt=defaultTimeSlice;
	starting=new MainT();
	starting->myPCB->stanje=PCB::READY;
	PCB::running=starting->myPCB;
	idle->start();
}

void System::kraj(){
	delete idle->myPCB;
	delete starting->myPCB;
	cnt=0;
}

void System::inic(){
	asm{
		cli
			push es
			push ax
			mov ax,0
			mov es,ax
			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax
			mov word ptr es:0022h, seg timer
			mov word ptr es:0020h, offset timer
			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax
			pop ax
			pop es
			sti
	}
}

void System::restore(){
	asm {
		cli
		push es
		push ax
		mov ax,0
		mov es,ax
		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax
		pop ax
		pop es
		sti
	}
}


void System::dispatch(){
	lock
	naZahtev=1;
	timer();
	unlock
}
