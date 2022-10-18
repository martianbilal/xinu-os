/* resptime.c - resptime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resptime  - time spent by the process in the kernel 
 *------------------------------------------------------------------------
 */

syscall resptime(
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

    // dbg_pr("pid in totcpu input : %d", pid);
    prptr = (struct procent *) &proctab[pid];
    
    if(prptr->prcurrcount == 0) {
        // cant do the calculation 
        //* divide by zero problem 

        restore(mask);
        return SYSERR;
    }

    /**
     * time spent in the ready state by the process
    */

    retval = ((uint32)prptr->prtotalresponse) / prptr->prcurrcount;
    retval = retval / 1000;
    
    restore(mask);
	return retval;
}
