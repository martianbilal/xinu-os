/* insertdynq.c - insertdynq */

#include <xinu.h>



short push_fifo_queue(
    short tail,
    pid32 queue[],
    pid32 pid
)
{
    queue[tail] = pid;
    tail = (tail + 1) % NPROC;
    return OK;
}

/*------------------------------------------------------------------------
 *  insertdynq  -  insert a process into a dynamic queue
 *------------------------------------------------------------------------
 */
short insertdynq(
    pri16  prio,        /* priority of process to insert      */
    pid32  pid          /* process id of process to insert    */
)
{
	intmask 	mask;    	/* Interrupt mask		*/
	// struct	procent *prptr;		/* Ptr to process's table entry	*/
    struct mfeedbqx *dynptr;  /* Ptr to dynamic queue entry */

    mask = disable();
    

    if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

    // prptr = &proctab[newpid];
    dynptr = &dynqueue[prio];

    if(dynptr->count >= NPROC) {
        restore(mask);
        return SYSERR;
    }
    
    if(push_fifo_queue(dynptr->tail, dynptr->fifoqueue, pid)) {
        //success
        dynptr->count = dynptr->count + 1;         
    }
    else {
        //failure
        restore(mask);
        return SYSERR;
    }

    restore(mask);
    return 0;
}

