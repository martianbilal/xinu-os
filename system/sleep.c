/* sleep.c - sleep sleepms */

#include <xinu.h>

#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 *  sleep  -  Delay the calling process n seconds
 *------------------------------------------------------------------------
 */
syscall	sleep(
	  int32	delay		/* Time to delay in seconds	*/
	)
{
	if ( (delay < 0) || (delay > MAXSECONDS) ) {
		return SYSERR;
	}
	sleepms(1000*delay);
	return OK;
}

/*------------------------------------------------------------------------
 *  sleepms  -  Delay the calling process n milliseconds
 *------------------------------------------------------------------------
 */
syscall	sleepms(
	  int32	delay			/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/

	if (delay < 0) {
		return SYSERR;
	}

	if (delay == 0) {
		yield();
		return OK;
	}

	/* Delay calling process */

	mask = disable();
	if (insertd(currpid, sleepq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}


	proctab[currpid].prstate = PR_SLEEP;	

	/* Promote the process before blocking */
	#ifdef DYN_SCHED
	// dbg_pr("[DYN sched]promoting pid : %d from %d ", currpid, proctab[currpid].prprio);
	if(proctab[currpid].prprio != 10) {
		proctab[currpid].prprio = getslpret(proctab[currpid].prprio);
	}
	// dbg_pr("to %d\n", proctab[currpid].prprio);
	#endif
	
	resched();
	restore(mask);
	return OK;
}
