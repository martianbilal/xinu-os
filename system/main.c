/*  main.c  - main */

#include <xinu.h>

void prcpuhungryPrint(void);
void cpuhungryProc(void);
void iohungryProc(void);


void sndA(void), sndB(void);
void printClockCounters(void);



process	main(void)
{
    
    	// kprintf("\nHello World!\n");
    	// kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
    	// kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
    	// kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
    	// kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
    	// kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
    	// kprintf("\n...creating a shell\n");

	/* Run the Xinu shell */

	// recvclr();
	// resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	// resume(create(sndA, 1024, 0, "proc 1", 0));
	// resume(create(sndB, 1024, 0, "proc 2", 0));

	// create2(sndA, 1024, 0, "proc 1", 0);
	// create2(sndB, 1024, 0, "proc 2", 0);

	/* Wait for shell to exit and recreate it */

	// while (TRUE) {
	// 	receive();
	// 	sleepms(200);
	// 	kprintf("\n\nMain process recreating shell\n\n");
	// 	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	// }

	kprintf("\nTest process running code of main():%d\n", currpid);
	
	printClockCounters();
	// sleep(5);
	// printClockCounters();

	resume(create(cpuhungryProc, 1024, 20, "cpuhungry", 0));
	resume(create(iohungryProc, 1024, 20, "iohungry", 0));

	kprintf("\n[Debug] Running experiment to check the effectiveness of the prcpuhungry\n");
	

	kprintf("Test result of addfour : 5 + 34 + 234 + 3 = %d\n", addfour(5,34, 234, 3));
	kprintf("Test result of testgreaterfirst : 5,64 = %d\n", testgreaterfirst(5,64));
	kprintf("Test result of testgreaterfirst : 64,5 = %d\n", testgreaterfirst(65,5));
	kprintf("Test result of testgreaterfirst : 5,5 = %d\n", testgreaterfirst(5,5));

	return OK;
    
}

void printClockCounters(void){
	kprintf("\nvfineclkcounter : %u\n", vfineclkcounter);
	kprintf("\nfineclkcounter : %u\n", fineclkcounter);
	// kprintf("\nclktime : %u\n", clktime)
	return;
}

/*------------------------------------------------------------------------
* sndA - Repeatedly emit ’A’ on the console without terminating
*------------------------------------------------------------------------
*/
void sndA(void)
{
	while(1)
		kputc('A');
}


/*------------------------------------------------------------------------
* sndB - Repeatedly emit ’B’ on the console without terminating
*------------------------------------------------------------------------
*/
void sndB(void)
{
	while(1)
		kputc('B');
}


/*------------------------------------------------------------------------
* prcpuhungryPrint - print the prcpuhungry values for the current process 
*------------------------------------------------------------------------
*/
void prcpuhungryPrint(void)
{
	struct procent *prptr; /* Pointer to process */

	prptr = &proctab[currpid];

	kprintf("\n[Debug] [%d] prcpuhungry : %u\n", currpid, prptr->prcpuhungry);
}

/*------------------------------------------------------------------------
* cpuhungryProc - is cpu hungry lol
*------------------------------------------------------------------------
*/
void cpuhungryProc(void)
{
	kprintf("\n[%d] cpuhungrycalled\n", currpid);
	prcpuhungryPrint();
	int a = 1;
	int i = 0;
	int b = 1;

	while(i < 5000000) {
		a = (a + 1) * 20 / a;
		b = a + b * b / 2 / 4 * a ;
		i = i + 1;
	}
	prcpuhungryPrint();

	return;
}

/*------------------------------------------------------------------------
* iohungryProc - is io hungry :)
*------------------------------------------------------------------------
*/
void iohungryProc(void)
{
	kprintf("\n[%d] iohungrycalled\n", currpid);
	prcpuhungryPrint();
	int i = 0;

	while(i < 5000000) {
		kprintf("");
		i = i + 1;
	}
	prcpuhungryPrint();
	
	return;
}