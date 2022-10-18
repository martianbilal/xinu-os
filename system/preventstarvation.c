#include <xinu.h>


/*------------------------------------------------------------------------
 *  preventstarvation  - prevent starvation
 *------------------------------------------------------------------------
 */
void preventstarvation(
    void
)
{
    struct mfeedbqx *dynptr;  /* Ptr to dynamic queue entry */
    struct procent *prptr;  /* Ptr to process table entry */
    int temp = 0;
    int i;  /* for loop iterator */
    pid32 pid; /* pid of process to be inserted into new list */

    intmask 	mask;    	/* Interrupt mask		*/
    mask = disable();

    for(i = 0; i < 10; i++) {
        dynptr = &dynqueue[i];
        prptr = &proctab[dynptr->fifoqueue[dynptr->head]];

        if(dynptr->count ) {
            if(prptr->prmaxresponse > STARVATIONTHRESHOLD) {
                temp = i + PRIOBOOST;
                
                if(temp > 9) {
                    temp = 9;
                }


                // check if the process is already in the new list
                if(temp <= i) {
                    continue;
                }
                
                dynptr->count = dynptr->count - 1;
                
                // extract from list
                pid = dynptr->fifoqueue[dynptr->head];
                dynptr->head = (dynptr->head + 1) % NPROC;
                
                insertdynq(pid, temp);
            }
        }
    }

    restore(mask);
    return;
}