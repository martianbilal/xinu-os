/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	#if (STARVATIONPREVENT == 1)
	static uint32 count_starve = STARVATIONPERIOD; /* Count to STARVATIONPERIOD */
	#endif


	vfineclkcounter++;
	struct procent *prptr;

	prptr = &proctab[currpid];
	prptr->prusercpu = prptr->prusercpu + 1;


	#if (STARVATIONPREVENT == 1)
	/* Decrement the starvation counter */
	// dbg_pr("Decrementing starvation counter: %u", count_starve);
	if((--count_starve) <= 0) {
		// dbg_pr("Decrementing starvation counter");

		count_starve = STARVATIONPERIOD;
		preventstarvation();
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
		
		#ifdef TEST_DYNSCHED
		prptr->preempt2True = 1;
		#else
		prptr->prpreemptcount2 = prptr->prpreemptcount2 + 1;
		#endif

		prptr->prevtimeslice = preempt;
		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {

		#ifdef TEST_DYNSCHED
		prptr->preempt1True = 1;
		#else
		prptr->preemptcount1 = prptr->preemptcount1 + 1;
		#endif


		// process is preempted => cpu bound process
		// update its priority before it is rescheduled

		#ifdef DYN_SCHED
		prptr->prprio = gettqexp(prptr->prprio);
		preempt = getquantum(prptr->prprio);
		#else
		preempt = QUANTUM;
		#endif
		
		resched();
	}
}
