/* usercpu.c - usercpu */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  usercpu  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */

syscall usercpu(
    pid32 pid
)
{   
    intmask mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
    int32 retval;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

    prptr = (struct procent *) &proctab[pid];
    
    /**
     * usercpu time for this pid
    */
    retval = prptr->prusercpu;

    restore(mask);
	return retval;
}
