/*  main.c  - main */

#include <xinu.h>

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

	kprintf("\nTest process running code of main():%d\n", getpid());
	// printClockCounters();
	// sleep(5);
	// printClockCounters();

	return OK;
    
}

void printClockCounters(void){
	kprintf("\nfineclkcounter : %u\n", fineclkcounter);
	kprintf("\nvfineclkcounter : %u\n", vfineclkcounter);
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