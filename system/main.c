/*  main.c  - main */

#include <xinu.h>

void printsomething(){
	kprintf("printsomething\n");

	return;
}

void printsomethingblocked(){
	kprintf("blockedprintsomethingblocked\n");

	return;
}

void stupidprocess(){
	kprintf("stupidprocess\n");
	alarmx(2000, printsomethingblocked);
	sleep(3);
	kprintf("stupidprocess: received\n");
	while(1){
		;// do nothing
	}
	return;
}

process	main(void)
{
    pid32 pid;

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
	alarmx(2, printsomething);
	pid = create(stupidprocess, 4096, 20, "stupid", 1, CONSOLE);
	resume(pid);
	send(pid, 1);
	while (TRUE)
	{
		;
	}
	

	return OK;
    
}
