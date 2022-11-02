/* wakeup.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	pid32 pid;
	struct procent *prptr;

	/* Awaken all processes that have no more time to sleep */

	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		pid = dequeue(sleepq);
		if(pid < NPROC){
			ready(pid);
		} else if (pid >= NPROC && pid < (3*NPROC)) {
			// [BILAL] extract actual pid first
			prptr = &proctab[pid % NPROC];
			kprintf("[DBG] got a wakeup call for alarm process %s\n", prptr->prname);
			kprintf("[DBG] pid %d\n", pid);
			prptr->prmakedetour = 1;
			prptr->prnumalarms = prptr->prnumalarms - 1;

			// (*prptr->prcbftn)();
		}
	}

	resched_cntl(DEFER_STOP);
	return;
}
