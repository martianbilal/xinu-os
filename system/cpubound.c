#include <xinu.h>


/*
    *------------------------------------------------------------------------
    *  cpubound  -  run a cpubound process
    *------------------------------------------------------------------------
*/

void cpubound(
    void
)
{
    int init_time = vfineclkcounter;

    struct procent *prptr = &proctab[currpid];

    while((vfineclkcounter - init_time) < STOPTIME)
    {
        // do nothing
    }

    // ((uint32)prptr->prtotalresponse / prptr->prcurrcount) / 1000
    kprintf("cpubound,%d,%u,%u,%u,%u,%u,%u,%u\n", currpid, (uint32)prptr->prtotalcpu / 1000,
        prptr->prusercpu, ((uint32)prptr->prtotalresponse / prptr->prcurrcount) / 1000, 
        prptr->prmaxresponse, prptr->prcurrcount,
        prptr->prpreemptcount1, prptr->prpreemptcount2);
    
    return;
}