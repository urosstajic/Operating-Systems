/*
 * Queue.h
 *
 *  Created on: Jul 31, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_

class PCB;

class Queue {
public:
	Queue();
	~Queue();
	void dodaj(PCB* p);
	void izbaci(PCB* p);
	PCB* dohvati();
	int vel;
	void prodjiKrozListu();
	int daLiSadrzi(PCB* p);

private:
	struct Elem{
			Elem* sled;
			PCB* pcb;
			Elem(PCB* p){
				pcb=p;
				sled=0;
			}
		};
	Elem *prvi,*posl;

};

#endif /* QUEUE_H_ */
