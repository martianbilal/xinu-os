/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	#ifdef STARVATIONPREVENT
	static uint32 count_starve = STARVATIONPERIOD; /* Count to STARVATIONPERIOD */
	#endif

	struct procent *prptr;

	prptr = &proctab[currpid];
	prptr->prusercpu = prptr->prusercpu + 1;


	#ifdef STARVATIONPREVENT
	/* Decrement the starvation counter */
	if((--count_starve) <= 0) {
		preventstarvation();
		count_starve = STARVATIONPERIOD;
	}
	#endif

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
		prptr->preempt1True = 1;
		preempt = QUANTUM;
		resched();
	}
}
