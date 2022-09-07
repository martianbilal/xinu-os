/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	static 	uint32 count10 = 10; 	/* Count to 10ms */
	struct procent *prptr; /* Pointer to pro*/


	prptr = &proctab[getpid()];

	/* Decrement the ms counter and see if 10ms have passed */
	if((--count10) <= 0) {
		
		/* 10 ms have passed */
		
		fineclkcounter++;

		/* Reset the local ms counter for next 10 ms */
		count10 = 10;
	}

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		prptr->prcphungry = 0;
		resched();
	}
}
