/*
 * KernelL.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef KERNELL_H_
#define KERNELL_H_

#include "KernelS.h"

class KernelL {
public:
	KernelL();
	virtual ~KernelL();
	void dodaj(KernelS* ks);
	void izbaci(KernelS* ks);
	void provera();
	void povecajValue(PCB* p);

private:
	struct Elemm{
			Elemm* sled;
			KernelS* kern;
			Elemm(KernelS* k){
				kern=k;
				sled=0;
		}
	};
	Elemm* prvi,*posl;
	int num;
};

#endif /* KERNELL_H_ */
