/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	
	/* marks the start of the waiting phase */
	prptr->prreadystart = getticks();
	#ifdef DYN_SCHED
	// dbg_pr("[DYN sched]inserting pid : %d\n", pid);
	insertdynq(prptr->prprio, pid);
	#else
	dbg_pr("inserting pid : %d\n", pid);
	insert(pid, readylist, prptr->prprio);
	#endif
	resched();

	return OK;
}
