/* totcpu.c - totcpu */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  totcpu  - time spent by the process in the kernel 
 *------------------------------------------------------------------------
 */

syscall totcpu(
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
    
    /**
     * time spent in the kernel by the process
    */
    retval = (prptr->prtotalcpu) / 1000;

    restore(mask);
	return retval;
}
