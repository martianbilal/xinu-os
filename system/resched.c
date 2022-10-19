/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	uint32	tempresponse;	/* holding the response time temporarily*/
	/* If rescheduling is deferred, record attempt and return */
	uint32 temppid = currpid;

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		
		#ifdef DYN_SCHED
		if (ptold->prprio > inspectmaxprio()) {
			return;
		}
		#else
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}
		#endif

		/* Old process will no longer remain current */
		ptold->prstate = PR_READY;
		/* marks the start of the waiting phase */
		ptold->prreadystart = getticks();


		if(ptold->preempt2True) {
			ptold->useprevtimeslice= 1;
		}
		#ifdef DYN_SCHED
		// dbg_pr("[DYN sched]inserting pid : %d\n", currpid);
		insertdynq(ptold->prprio, currpid);
		#else
		insert(currpid, readylist, ptold->prprio);
		#endif
	}

	/* Force context switch to highest priority ready process */
	currstop = getticks();
	ptold->prtotalcpu = ptold->prtotalcpu + ((uint32)(currstop - currstart) / 389);
	// dbg_pr("[id : %d] prtotalcpu : %u\n", currpid, ptold->prtotalcpu);
	// dbg_pr("[id : %d]  currstart: %u\n", currpid, currstart);
	// dbg_pr("[id : %d]  currstop: %u\n", currpid, currstop);
	
	// dbg_pr("[%d] resched called\n", currpid);
	#ifdef DYN_SCHED
	// dbg_pr("we are getting next process from dynamic scheduler\n");
	currpid = extractdynq();
	if( currpid == SYSERR ) {
		currpid = NULLPROC;
	} 
	// dbg_pr("[DYN SCHED]currpid : %d\n", currpid);
	// dbg_pr("[DYN SCHED]tempid : %d\n", temppid);

	#else
	currpid = dequeue(readylist);

	// dbg_pr("currpid : %d\n", currpid);
	// dbg_pr("tempid : %d\n", temppid);
	
	#endif



	// dbg_pr("[%d] currpid\n", currpid);

	ptnew = &proctab[currpid];
	currstart = getticks();
	ptnew->prstate = PR_CURR;
	#ifdef DYN_SCHED
	preempt = getquantum(ptnew->prprio);
	#else
	preempt = QUANTUM;
	#endif
	if(ptnew->useprevtimeslice) {
		preempt = ptnew->prevtimeslice;
		ptnew->useprevtimeslice = 0;
	}
	// udpate the value of the prcurrcount here : 
	ptnew->prcurrcount = ptnew->prcurrcount + 1;
	// adding the time spent in the ready queue to the totalresponse
	tempresponse = ((uint32)(currstart - ptnew->prreadystart)) / 389;
	if((tempresponse / 1000) > ptnew->prmaxresponse) {
		// change the maxresponse 
		ptnew->prmaxresponse = tempresponse / 1000;
	}

	ptnew->prtotalresponse = (uint32)ptnew->prtotalresponse + tempresponse;
	// dbg_pr("[id : %d] prtotalresponse : %u\n", currpid, ptnew->prtotalresponse);

	
	#ifdef TEST_DYNSCHED
	// if(ptnew->prusercpu > 5000) {
	// 	dbg_pr("pid: %d, priorirty : %u", currpid, ptnew->prprio);
	// }


	if(!(temppid == currpid)){	// process is actually changing
		if( ptold->preempt1True ){	// if the process was preempted by time slice depletion
			ptold->preempt1True = 0;
			ptold->prpreemptcount1 = ptold->prpreemptcount1 + 1;
		} 
		if( ptold->preempt2True ){	// if the process was preempted through wakeup
			ptold->preempt2True = 0;
			ptold->prpreemptcount2 = ptold->prpreemptcount2 + 1;
		}
	}
	// reset indicators 
	ptold->preempt1True = 0;
	ptold->preempt2True = 0;
	#endif
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	// struct procent *prptr; 

	// prptr = &proctab[currpid];

	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			// #ifdef TEST_DYNSCHED
			// prptr->preempt2True = 1;
			// #else
			// prptr->prpreemptcount2 = prptr->prpreemptcount2 + 1;
			// #endif
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
