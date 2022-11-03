/*  main.c  - main */

#include <xinu.h>

static pid32 producer1, producer2, consumer1, consumer2, consumer3, consumer4;

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
	alarmx(100, printsomethingblocked);
	sleep(2.5);
	kprintf("stupidprocess: received\n");
	while(1){
		;// do nothing
	}
	return;
}


void producerProc(){
	char sendbuf[12] = "hello world"; 
	kprintf("producer\n");
	sendx(consumer1, sendbuf, 12);
	// kprintf("sent to consumer1\n");
	sendx(consumer2, sendbuf, 12);
	// kprintf("sent to consumer2\n");
	sendx(consumer3, sendbuf, 12);
	// kprintf("sent to consumer2\n");
	sendx(consumer4, sendbuf, 12);
	// kprintf("sent to consumer3\n");
	sendx(consumer2, sendbuf, 12);
	// kprintf("sent to consumer4\n");

	while(1){
		;// do nothing
	}
	return;
}

void consumerProc(){
	char recvbuf[12];
	int i = 0;
	kprintf("consumer\n");
	receivex(&producer1, recvbuf, 12);
	kprintf("consumer: [%d] received [%s] from producer %d \n", currpid, recvbuf, producer1);
	// for(i = 0; i < 12; i++){
	// 	kprintf("recved : %c\n", recvbuf[i]);
	// }
	while(1){
		;// do nothing
	}
	return;
}

process	main(void)
{
    // pid32 pid;

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
	producer1 = create(producerProc, 8192, 20, "producer1", 1, CONSOLE);
	producer2 = create(producerProc, 8192, 20, "producer2", 1, CONSOLE);
	consumer1 = create(consumerProc, 8192, 20, "consumer1", 1, CONSOLE);
	consumer2 = create(consumerProc, 8192, 20, "consumer2", 1, CONSOLE);
	consumer3 = create(consumerProc, 8192, 20, "consumer3", 1, CONSOLE);
	consumer4 = create(consumerProc, 8192, 20, "consumer4", 1, CONSOLE);
	
	resume(consumer1);
	resume(consumer2);
	resume(consumer3);
	resume(consumer4);
	resume(producer1);
	resume(producer2);


	// /* Wait for shell to exit and recreate it */

	// while (TRUE) {
	// 	receive();
	// 	sleepms(200);
	// 	kprintf("\n\nMain process recreating shell\n\n");
	// 	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	// }
	// alarmx(2, printsomething);
	// pid = create(stupidprocess, 4096, 20, "stupid", 1, CONSOLE);
	// resume(pid);
	// send(pid, 1);
	while (TRUE)
	{
		;
	}
	

	return OK;
    
}
