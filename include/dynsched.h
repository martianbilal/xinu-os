#ifndef DYNSCHED_H

#define DYNSCHED_H



// uncomment to use preempt*true indicators
#define TEST_DYNSCHED

#define TSXINIT 4

// uncomment to enable dynamic scheduling
#define DYN_SCHED              

struct tsx_disp {
  unsigned short  tqexp;         // new priority: CPU-bound (time quantum expired)
  unsigned short  slpret;        // new priority: I/O-bound (sleep return)
  unsigned short  quantum;       // new time slice
};

struct mfeedbqx {
  pid32 fifoqueue[NPROC];	// circular FIFO buffer of PIDs
  short head;       		// index of head of FIFO buffer
  short tail;       		// index of tail of FIFO buffer
  short count;			// number of processes in the queue
};


#endif