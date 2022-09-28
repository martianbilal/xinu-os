/* cpuutil.c - cpuutil */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cpuutil  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */

unsigned short cpuutil(
    void
)
{   
    double retval;
    pid32 null_pid = 0;

    retval = usercpu(null_pid);


    retval = retval/vfineclkcounter;
    

    retval = retval * 100; 

	return (unsigned short )retval;
}
