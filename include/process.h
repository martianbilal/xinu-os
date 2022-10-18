/* process.h - isbadpid */

/* Maximum number of processes in the system */

#ifndef NPROC
#define	NPROC		8
#endif		


#include <dynsched.h>

/* Process state constants */

#define	PR_FREE		0	/* Process table entry is unused	*/
#define	PR_CURR		1	/* Process is currently running		*/
#define	PR_READY	2	/* Process is on ready queue		*/
#define	PR_RECV		3	/* Process waiting for message		*/
#define	PR_SLEEP	4	/* Process is sleeping			*/
#define	PR_SUSP		5	/* Process is suspended			*/
#define	PR_WAIT		6	/* Process is on semaphore queue	*/
#define	PR_RECTIM	7	/* Process is receiving with timeout	*/

/* Miscellaneous process definitions */

#define	PNMLEN		16	/* Length of process "name"		*/
#define	NULLPROC	0	/* ID of the null process		*/

/* Process initialization constants */

#define	INITSTK		65536	/* Initial process stack size		*/
#define	INITPRIO	20	/* Initial process priority		*/
#define	INITRET		userret	/* Address to which process returns	*/

/* Inline code to check process ID (assumes interrupts are disabled)	*/

#define	isbadpid(x)	( ((pid32)(x) < 0) || \
			  ((pid32)(x) >= NPROC) || \
			  (proctab[(x)].prstate == PR_FREE))

/* Number of device descriptors a process can have open */

#define NDESC		5	/* must be odd to make procent 4N bytes	*/

/* Definition of the process table (multiple of 32 bits) */

struct procent {		/* Entry in the process table		*/
	uint16	prstate;	/* Process state: PR_CURR, etc.		*/
	pri16	prprio;		/* Process priority			*/
	char	*prstkptr;	/* Saved stack pointer			*/
	char	*prstkbase;	/* Base of run time stack		*/
	uint32	prstklen;	/* Stack length in bytes		*/
	char	prname[PNMLEN];	/* Process name				*/
	sid32	prsem;		/* Semaphore on which process waits	*/
	pid32	prparent;	/* ID of the creating process		*/
	umsg32	prmsg;		/* Message sent to this process		*/
	bool8	prhasmsg;	/* Nonzero iff msg is valid		*/
	int16	prdesc[NDESC];	/* Device descriptors for process	*/
	uint32 	prusercpu;	/* process utilization time in miliseconds */
	uint32	prtotalcpu;	/* records the total cpu time (kernel + user) in microseconds */
	uint16	prcurrcount;	/* counts the number of times a process have been ctxswed out */
	uint64	prreadystart;	/* record when a process has entered the ready state 	 */
	uint64	prtotalresponse;	/* record the time took to go from the ready to the curr */
	uint32	prmaxresponse;	/* record the max time spent by this process in the ready queue */
	uint16	prpreemptcount1;
	uint16	prpreemptcount2;
	uint16	preempt1True; 
	uint16	preempt2True;
}; 


/* Marker for the top of a process stack (used to help detect overflow)	*/
#define	STACKMAGIC	0x0A0AAAA9

extern	struct	procent proctab[];
extern	struct	tsx_disp	dyndisp[];	/* dynamic scheduler dispatch table */
extern	struct	mfeedbqx	dynqueue[];	/* dynamic scheduler queue */
extern	int32	prcount;	/* Currently active processes		*/
extern	pid32	currpid;	/* Currently executing process		*/
extern	uint64	currstart;	/* Starting time of currently running process */
extern	uint64	currstop;	/* Stopping time of currently running process */


#define DEBUG_BILAL 3

#if defined(DEBUG_BILAL) && DEBUG_BILAL > 0
	#define dbg_pr(fmt, args...) kprintf("\n DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args, "\n")
#else
	#define dbg_pr(fmt, args...) /* Don't do anything in release builds */
#endif