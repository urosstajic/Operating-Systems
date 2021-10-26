#include <stdio.h>
#include "System.h"

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]){
	System::pocetak();
	System::inic();
	int i=userMain(argc,argv);
	System::restore();
	System::kraj();
	return i;
}
