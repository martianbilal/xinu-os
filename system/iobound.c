#include <xinu.h>


/*
    *------------------------------------------------------------------------
    *  iobound  -  run an iobound process
    *------------------------------------------------------------------------
*/

void iobound(
    void
)
{
    int init_time = vfineclkcounter;
    int i;
    int nested_time = 0;

    struct procent *prptr = &proctab[currpid];

    while((vfineclkcounter - init_time) < STOPTIME)
    {   
        nested_time = vfineclkcounter;
        // do nothing
        for(i = 0; i < 100000; i++)
        {
            if((vfineclkcounter - nested_time) > 3)
            {
                break;
            }
           
        }
        sleepms(10);
    }

    kprintf("iobound,%d,%u,%u,%u,%u,%u,%u,%u\n", currpid, (uint32)prptr->prtotalcpu / 1000,
        prptr->prusercpu, ((uint32)prptr->prtotalresponse / prptr->prcurrcount) / 1000, 
        prptr->prmaxresponse, prptr->prcurrcount,
        prptr->prpreemptcount1, prptr->prpreemptcount2);
    
    return;
}