/* extractdynq.c - extractdynq */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  extractdynq  -  extract a process from a dynamic queue
 *------------------------------------------------------------------------
 */
short extractdynq(
    void
)
{
	intmask 	mask;    	/* Interrupt mask		*/
	// // struct	procent *prptr;		/* Ptr to process's table entry	*/
    struct mfeedbqx *dynptr;  /* Ptr to dynamic queue entry */
    int i;  /* for loop iterator */
    pid32 pid; /* pid of process to be extracted */

    mask = disable();

    // RT scheduling
    


    for(i = 10; i >= 0; i--) {
        dynptr = &dynqueue[i];
    
        if(dynptr->count){
            dynptr->count = dynptr->count - 1;

            // could be converted into a pop function
            pid = dynptr->fifoqueue[dynptr->head];
            dynptr->head = (dynptr->head + 1) % NPROC;
            if(pid == 73) {
                // dbg_pr("[pid  = 73]Level %d has %d processes\n", i, dynptr->count);
                // dbg_pr("[pid  = 73]Level %d has %d processes\n", 9, dynptr->count);

            }
            restore(mask);
            return pid;
        }
    }


    // if (isbadpid(pid)) {
	// 	restore(mask);
	// 	return SYSERR;
	// }

    // prptr = &proctab[newpid];
    // dynptr = &dynqueue[prio];

    // if(dynptr->count >= NPROC) {
    //     restore(mask);
    //     return SYSERR;
    // }
    
    // if(push_fifo_queue(dynptr->tail, dynptr->fifoqueue, pid)) {
    //     //success
    //     dynptr->count = dynptr->count + 1;         
    // }
    // else {
    //     //failure
    //     restore(mask);
    //     return SYSERR;
    // }

    restore(mask);
    return SYSERR;
}

