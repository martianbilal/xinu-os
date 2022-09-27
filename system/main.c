/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	int pid = 0;
	uint32 ret_addr = 0; 
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

	kprintf("\nkstack[getpid] : %d\n", kstack[getpid()]);
	// kprintf("\ngetpid : %d\n", getpidx());
	pid = getpidx();
	kprintf("\n pid : %d\n", pid);

	ret_addr = (uint32)getmemx(4);
	kprintf("\n ret_addr : %d\n", ret_addr);
	

	return OK;
    
}
