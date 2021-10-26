/*
 * System.h
 *
 *  Created on: Jul 31, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <dos.h>
#include <iostream.h>

class IdleT;
class Thread;
class MainT;

#define lock asm{pushf;cli;}
#define unlock asm popf

class System {
public:
	//friend class Thread;
	System();
	static void pocetak();
	static void kraj();
	static void inic();
	static void restore();
	static void dispatch();
	static MainT* starting;
	static IdleT* idle;

};

#endif /* SYSTEM_H_ */
