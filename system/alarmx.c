/* alarmx.c - alarmx */

#include <xinu.h>

int isbadalarmX(uint32 timeval) {
	struct procent *prptr;

	prptr = &proctab[currpid];
	
	if (timeval < 0 || prptr->prnumalarms >= ALARM_COUNT) {
		return TRUE;
	}
	return FALSE;
}

/*------------------------------------------------------------------------
 *  alarmx  -  register a function ftn to be called after timeval milliseconds
 *------------------------------------------------------------------------
 */
syscall	alarmx(
	  uint32 timeval,		/* Time to wait in milliseconds	*/ 
	  void (* ftn) (void)	/* function to be called after the time interval passed	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct procent *prptr;		/* Ptr to process' table entry	*/
	pid32 pidalarm;			/* pid of alarm process		*/
	uint32 ret;

	mask = disable();

	prptr = &proctab[currpid];

	
	if (isbadalarmX(timeval) || ftn == NULL) {
		restore(mask);
		return SYSERR;
	}


	/*
		if waiting time is 0 ms, call the function immediately
	*/
	if (timeval == 0) {
		(*ftn)();
		restore(mask);
		return OK;
	}

	/*
		if waiting time is greater than 0 ms, register the function
	*/
	prptr->prnumalarms = prptr->prnumalarms + 1;

	// add the callback functoin
	prptr->prcbftn = ftn;

	// setting the pidalarm value 
	// if 0 alarms, NPROC + currpid, else (no. of alarms + 1)*NPROC + currpid + 1
	pidalarm = (prptr->prnumalarms) * NPROC + currpid;
	
	// adding the alarm to the sleep queue
	ret = insertd(pidalarm, sleepq, timeval);
	// kprintf("[DBG] alarmx: inserted alarm %d in sleepq with key %d for %d and got result : %d\n", pidalarm, timeval, currpid, ret);

	restore(mask);
	return OK;
}
