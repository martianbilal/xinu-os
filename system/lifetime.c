/* lifetime.c - lifetime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  lifetime  -  give lifetime of a process
 *------------------------------------------------------------------------
 */
syscall	lifetime(
	  pid32     pid		/* pid of the process	*/
	)
{
	intmask		mask;		/* Saved interrupt mask		*/
	// struct	dentry	*devptr;	/* Entry in device switch table	*/
    struct procent *prptr;  /* process pointer for pid */ 
	int32		retval;		/* Value to return to caller	*/

	mask = disable();
    
    if (isbadpid(pid)) {
        restore(mask);
        return SYSERR;
    }

    prptr = &proctab[pid];
	retval = fineclkcounter - prptr->prbirthday;
	restore(mask);
	return retval;
}
