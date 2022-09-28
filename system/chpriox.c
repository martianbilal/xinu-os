/* chpriox.c - chpriox */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  chpriox  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
pri16	chpriox(
	  pid32		pid,		/* ID of process to change	*/
	  pri16		newprio		/* New priority			*/
	)
{
	int ret = 0;
	__asm__ __volatile__ (
		"movl %[SYS_NUM], %%eax;"
		"movl %[id], %%ebx;"
		"pushl %%ebx;"
		"movl %[prio], %%ebx;"
		"pushl %%ebx;"
		"int $46;"
		"mov %%esi, %%eax;"
		"mov %%eax, %[retval];"
		"popl %%ebx"
		:[retval] "=rm"(ret)
		:[SYS_NUM] "0"(SYSCHPRIO), [id] "rm"((uint32)pid), [prio] "rm"(newprio)
		:"eax"
	);

	return (uint16)ret;
}
