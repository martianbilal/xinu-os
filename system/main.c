/*  main.c  - main */

#include <xinu.h>



process simpleProc(){
	int counter = 0;

	while(usercpu(getpid()) < 1000){
		counter++;
	}
	// kprintf("counter valua at the end of the process : %d", counter );
	kprintf("\n [Debug] [PID : %d] cpuutilization : %u\n", getpid(),cpuutil());
	return OK;
}




process prioCheckProc(){
	int counter = 0;

	while(usercpu(getpid()) < 1000){
		getprio(getpid());	
		counter++;
	}

	kprintf("\n [Debug] [PID : %d] cpuutilization : %u\n", getpid(),cpuutil());


	return OK;
}


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

	ret_addr = (uint32)getmemx(2);
	kprintf("\n ret_addr : %d\n", ret_addr);

	ret_addr = (uint32)usercpux(getpid());
	kprintf("\n ret_addr usercpu: %u\n", ret_addr);
	kprintf("\n ret_addr usercpu: %u\n", usercpu(getpid()));

	ret_addr = (uint32)chpriox(currpid, 20);
	kprintf("\n ret_addr : %d\n", ret_addr);

	// kprintf("\n cpuutilization : %u\n", cpuutil());

	
	kprintf("\n cpuutilization : %u\n", cpuutil());

	// resume(create(simpleProc, 4096, 10, "getprio-1", 0));
	// resume(create(simpleProc, 4096, 10, "getprio-2", 0));
	// resume(create(prioCheckProc, 4096, 10, "getprio-3", 0));
	// resume(create(prioCheckProc, 4096, 10, "getprio-4", 0));

	// resume(create(simpleProc, 4096, 18, "simple-1", 0));
	// resume(create(simpleProc, 4096, 18, "simple-2", 0));
	// resume(create(simpleProc, 4096, 18, "simple-3", 0));
	// resume(create(simpleProc, 4096, 18, "simple-4", 0));


	kprintf("\n cpuutilization : %u\n", cpuutil());


	return OK;
    
}
