/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendx(
		pid32 pid,
		char *buf,
		uint16 len
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to receiving process's table entry	*/
	struct	procent *senderptr;		/* Ptr to sender process's table entry	*/
	int i = 0; // [BILAL] counter for copying the message 

	mask = disable();
	if (isbadpid(pid) || isbadpid(currpid) || len > IPCX_MAXLEN) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];	/* Point to receiving process's table entry	*/
	senderptr = &proctab[currpid];	/* Point to sender process's table entry	*/

	wait(senderptr->pripc); // [BILAL] wait for the semaphore to be available for the receiver 

	// if another sender is blocked on the receiver return syserr
	if(prptr->prblockedsender != 0){
		restore(mask);
		return SYSERR;
	}	

	// [BILAL] [TODO] if the receiver buffer is empty copy the message to the receiver buffer
	if(prptr->prrecvlen == 0){
		// copy the message to the receiver buffer 
		for(i = 0; i < len; i++){
			prptr->prrecvbuf[i] = buf[i];
		}
		prptr->prrecvlen = len;
		prptr->prsenderpid = currpid;
		// if the receiver is blocked on the sender, ready the receiver
		if(prptr->prstate == PR_RECV){
			ready(pid);
		}
		goto res;
	}

	// if the receiver buffer is occupied [not empty] block
	if(prptr->prrecvlen != 0){
		prptr->prblockedsender = currpid;

		senderptr->prblockonreceiver = pid;
		senderptr->prstate = PR_SENDBLOCK;
		// copy the buffer to the sender's buffer 
		for(i = 0; i < len; i++){
			senderptr->prsndbuf[i] = buf[i];
		}
		senderptr->prsndlen = len;
		resched();
	} 

	signal(prptr->pripc);
	
res:
	restore(mask);		/* Restore interrupts */
	return OK;
}
