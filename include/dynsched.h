#ifndef DYNSCHED_H

#define DYNSCHED_H


#define TEST_DYNSCHED 1

#define TSXINIT 4

#define DYN_SCHED 1              // 1: dynamic scheduling, 0: fixed scheduling


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