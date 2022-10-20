/* inspectmaxprio.c - inspectmaxprio */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  inspectmaxprio  -  return the max priority of the ready list
 *------------------------------------------------------------------------
 */
pri16 inspectmaxprio(
    void
)
{
	intmask 	mask;    	/* Interrupt mask		*/
	// // struct	procent *prptr;		/* Ptr to process's table entry	*/
    struct mfeedbqx *dynptr;  /* Ptr to dynamic queue entry */
    int i;  /* for loop iterator */

    mask = disable();
    
    for(i = 10; i >= 0; i--) {
        dynptr = &dynqueue[i];
        if(dynptr->count){
            // success
            restore(mask);
            return i;
        }
    }

    // failure
    restore(mask);
    return SYSERR;
}

