/* executedetour.c - executedetour */

#include <xinu.h>

static unsigned long	prev_ip;
static unsigned long 	prev_cs;
static unsigned long 	prev_eflags;
static unsigned long 	prev_sp;
static unsigned long 	rest_ip;



/*------------------------------------------------------------------------
 *  executedetour  - execute detour
 *------------------------------------------------------------------------
 */
void	executedetour(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct procent *prptr;		/* Ptr to process' table entry	*/


	mask = disable();

	prptr = &proctab[currpid];
	
	if(prptr->prmakedetour == 1)
	{
		kprintf("process ready to execute detour %s\n", prptr->prname);
	}

	
	if(prptr->prmakedetour == 1 && prptr->prstate == PR_CURR) {
		kprintf("executedetour: %s\n", prptr->prname);

		// asm("pop %ebx");
		// asm("mov %ebx, prev_sp");
		// asm("pop %ebx");
		// asm("mov %ebx, prev_ip");
		// asm("pop %ebx");
		// asm("mov %ebx, prev_cs");
		// asm("pop %ebx");
		// asm("mov %ebx, prev_eflags");
		// asm("push prev_sp");


		// extended inline assembly
		asm("movl 40(%ebp), %ebx");
		asm("movl %ebx, prev_ip");
		asm("movl 44(%ebp), %ebx");
		asm("movl %ebx, prev_cs");
		asm("movl 48(%ebp), %ebx");
		asm("movl %ebx, prev_eflags");
		asm("movl (%ebp), %ebx");
		asm("movl %ebx, prev_sp");


		kprintf("prev_cs : 0x%04X\n", prev_cs);
		kprintf("prev_ip 0x%04X\n", prev_ip);
		kprintf("prev_eflags 0x%04X\n", prev_eflags);
		kprintf("prev_sp 0x%04X\n", prev_sp);
		kprintf("handler 0x%04X\n", prptr->prcbftn);
		prptr->prmakedetour = 0;


		// change the ip to the detour function
		prev_ip = (unsigned long) prptr->prcbftn;
		rest_ip = (unsigned long) restoreregs;
		
		// prptr->prcbftn();
		kprintf("mod prev_ip 0x%04X\n", prptr->prcbftn);
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, 40(%ebp)");
		
		// set up the stack for the iret detour
		asm("movl rest_ip, %ebx");
		asm("push %ebx");
		asm("movl prev_eflags, %ebx");
		asm("push %ebx");
		asm("movl prev_cs, %ebx");
		asm("pushl %ebx");
		asm("movl prev_ip, %ebx");
		asm("pushl %ebx");
		asm("pushal");

		// // change the return address of the current frame 
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, -4(%ebp)");
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, -8(%ebp)");

		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, 4(%ebp)");
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, (%ebp)");
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, 8(%ebp)");
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, 12(%ebp)");
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, 16(%ebp)");
		// asm("movl prev_ip, %ebx");
		// asm("movl %ebx, 20(%ebp)");


		kprintf("address of restoreregs : 0x%04X\n", restoreregs);
		kprintf("address of handler : 0x%04X\n", prptr->prcbftn);

		asm("jmp ret_from_executedetour");
		asm("sti");
		// asm("ret");
		asm("iret");
		// ===========
		// asm("mov prev_ip, %ebx");
		// asm("push %ebx");
		// asm("mov 0, %ebx");
		// // asm("pop %ebx");
		// asm("ret");
		kprintf("reached \n");

	} else {
		restore(mask);
		return;
	}

	
	restore(mask);
	return;
}
