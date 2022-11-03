/* receivex.c - receivex */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivex  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
syscall	receivex(
	pid32 *pidptr, 
	char *buf, 
	uint16 len
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *senderptr;		/* Ptr to sender process's table entry	*/
	struct	procent *recvrptr;		/* Ptr to receiver process's table entry	*/
	pid32 temppid = 0; // [BILAL] temporary pid to store the sender pid
	int i = 0; // [BILAL] counter for copying the message



	mask = disable();

	if (isbadpid(*pidptr) || isbadpid(currpid) || len > IPCX_MAXLEN) {
		restore(mask);
		return SYSERR;
	}


	// senderptr = &proctab[*pidptr];
	recvrptr = &proctab[currpid];


	// if no message in the buffer and no sender blocked, reciever should block
	if (recvrptr->prrecvlen == 0 && recvrptr->prblockedsender == 0) {
		recvrptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}

	// if message in buffer copy to the user 
	if(recvrptr->prrecvlen != 0){
		// copy the message to the user buffer 
		for(i = 0; i < len; i++){
			buf[i] = recvrptr->prrecvbuf[i];
		}
		// reset the buffer 
		recvrptr->prrecvlen = recvrptr->prrecvlen - len;
		if(recvrptr->prrecvlen < len){
			recvrptr->prrecvlen = 0;
		}
		// communicate the sender pid to the user 
		*pidptr = recvrptr->prsenderpid;

		if(recvrptr->prrecvlen == 0){
			// ready for copying the new message
			recvrptr->prsenderpid = 0;
		}
	} 


	// if there is a sender blocked on the receiver, copy the message from the sender's buffer to the receiver's buffer
	if(recvrptr->prblockedsender != 0 && recvrptr->prrecvlen == 0){

		temppid = recvrptr->prblockedsender;
		senderptr = &proctab[recvrptr->prblockedsender];

		// copy the message to the user buffer 
		for(i = 0; i < senderptr->prsndlen; i++){
			recvrptr->prrecvbuf[i] = senderptr->prsndbuf[i];
		}
		
		recvrptr->prrecvlen = senderptr->prsndlen;

		// reset the buffer 
		senderptr->prsndlen = 0;
		
		// communicate the sender pid to the user 
		*pidptr = recvrptr->prblockedsender;

		recvrptr->prblockedsender = 0;
		recvrptr->prsenderpid = temppid;
		senderptr->prblockonreceiver = 0;
		senderptr->prstate = PR_READY;
		ready(*pidptr);
	
	}



	restore(mask);
	return OK;
}
