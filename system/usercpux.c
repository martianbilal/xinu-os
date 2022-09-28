/* usercpux.c - usercpux */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  usercpux  -  Return the ID of the currently executing process
 *------------------------------------------------------------------------
 */
int32	usercpux(
	pid32 pid
)
{
	int32 ret=0;

	// __asm__ volatile (
	// 	"int $46;"
	// 	:"=am"((pid32)ret)
	// 	:"0"(SYSGETPID)
	// );

	__asm__ __volatile__ (
		"movl %[SYS_NUM], %%eax;"
		"movl %[pid], %%ebx;"
		"pushl %%ebx;"
		"int $46;"
		"mov %%esi, %%eax;"
		"mov %%eax, %[retval];"
		"popl %%ebx"
		:[retval] "=rm"(ret)
		:[SYS_NUM] "0"(SYSUSERCPU), [pid] "rm"((uint32)pid)
		:"eax"
	);

	// __asm__ __volatile__ ("movl %0, %%eax;" ::"I"(SYSGETPID):"eax");
	// __asm__ __volatile__ ("int $46;" :"=m"(ret)::"eax");
	// __asm__ __volatile__ ("movl %%eax, %0;":"=m"(ret)::"memory");

	// __asm__ __volatile__ ("nop");
	return ret;
}
