/* executedetour2.c - executedetour2 */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  executedetour2  - execute detour2
 *------------------------------------------------------------------------
 */
void	executedetour2(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct procent *prptr;		/* Ptr to process' table entry	*/


	mask = disable();

	prptr = &proctab[currpid];
	// kprintf("process ready to execute detour2 %s\n", prptr->prname);

	
	if(prptr->prmakedetour == 1)
	{
		kprintf("process ready to execute detour2 %s\n", prptr->prname);
	}

	
	if(prptr->prmakedetour == 1) {
		kprintf("executedetour2: %s\n", prptr->prname);
		prptr->prmakedetour = 0;
		prptr->prnumalarms = prptr->prnumalarms - 1;

		// [BILAL] call the callback function
		(*prptr->prcbftn)();
		restore(mask);
		return;
	} else {
		restore(mask);
		return;
	}

	
	restore(mask);
	return;
}
