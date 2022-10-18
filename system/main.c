/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    
    	kprintf("\nHello World!\n");
    	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
    	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
    	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
    	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
    	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
    	kprintf("\n...creating a shell\n");

	/* Run the Xinu shell */

	// recvclr();
	// resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	// /* Wait for shell to exit and recreate it */

	// while (TRUE) {
	// 	receive();
	// 	sleepms(200);
	// 	kprintf("\n\nMain process recreating shell\n\n");
	// 	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	// }


	dbg_pr("PRINTING THE TOTCPU AND THE USERCPU\n");
	dbg_pr("[%d]\ttotcpu : %u\n",getpid(), totcpu(getpid()));
	dbg_pr("[%d]\tusercpu : %u\n",getpid(), usercpu(getpid()));
	dbg_pr("[%d]\ttotcpu : %u\n", 1, totcpu(1));
	dbg_pr("[%d]\tusercpu : %u\n", 1, usercpu(1));
	dbg_pr("[%d]\ttotcpu : %u\n", 2, totcpu(2));
	dbg_pr("[%d]\tusercpu : %u\n", 2, usercpu(2));
	dbg_pr("NULLL PROC :: totcpu : %u\n", totcpu(0));
	dbg_pr("NULL PROC  :: usercpu : %u\n", usercpu(0));


	dbg_pr("PRINTING THE response times \n");
	dbg_pr("[%d]\tcurr resp time : %u\n",getpid(), resptime(getpid()));
	
	dbg_pr("[%d]\t2 resp time : %u\n", 2, resptime(2));
	dbg_pr("[%d]\t2 resp time : %u\n", 2, SYSERR == resptime(2));
	
	dbg_pr("[%d]\tcurr resp time : %u\n", 1, resptime(1));
	dbg_pr("[%d]\t1 resp time : %u\n", 1, SYSERR == resptime(2));

	dbg_pr("[%d]\tNULL resp time : %u\n", 0, resptime(0));
	dbg_pr("[%d]\tNULL resp time : %u\n", 0, SYSERR == resptime(2));
	


	return OK;
    
}
