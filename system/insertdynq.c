/* insertdynq.c - insertdynq */

#include <xinu.h>



short push_fifo_queue(
    struct  mfeedbqx *dynptr,
    pid32 pid
)
{
    dynptr->fifoqueue[dynptr->tail] = pid;
    dynptr->tail = (dynptr->tail + 1) % NPROC;
    return OK;
}

void print_queue(struct mfeedbqx *dynptr, pri16 prio) {
    int i;
    kprintf("Printing the queue at %d\n", prio);
    kprintf("head : %d, tail : %d, count : %d\n", dynptr->head, dynptr->tail, dynptr->count);
    for(i = 0; i < NPROC; i++) {
        kprintf("%d ", dynptr->fifoqueue[i]);
    }
    kprintf("\n");
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
	struct	procent *prptr;		/* Ptr to process's table entry	*/
    struct mfeedbqx *dynptr;  /* Ptr to dynamic queue entry */

    mask = disable();
    if (prio < 0) {
        restore(mask);
        return SYSERR;
    }
    if(isbadpid(pid) && pid != -1) {
        // dbg_pr("[pid : %d]problem is with the pid\n", pid);
    }
    if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

    prptr = &proctab[pid];
    dynptr = &dynqueue[prio];
    // dbg_pr("[pid : %d]Response of the insert dyn q : %d\n", pid, 0);
    // dbg_pr("[pid : %d]count for this level of q : %d\n", pid, dynptr->count);

    if(dynptr->count >= NPROC) {
        restore(mask);
        return SYSERR;
    }

    // dbg_pr("[pid : %d]problem is in the push function\n", pid);

    
    if(push_fifo_queue(dynptr, pid)) {
        //success
        prptr->prprio = prio;
        dynptr->count = dynptr->count + 1;         
    }
    else {
        //failure
        restore(mask);
        return SYSERR;
    }

    // print_queue(dynptr, prio);

    restore(mask);
    return 0;
}

