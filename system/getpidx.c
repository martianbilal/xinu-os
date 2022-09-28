/* getpidx.c - getpidx */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpidx  -  Return the ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid32	getpidx(void)
{
	pid32 ret=0;

	// __asm__ volatile (
	// 	"int $46;"
	// 	:"=am"((pid32)ret)
	// 	:"0"(SYSGETPID)
	// );

	__asm__ __volatile__ (
		"mov %[SYS_NUM], %%eax;"
		"int $46;"
		"mov %%esi, %%eax;"
		"mov %%eax, %[retval];"
		:[retval] "=rm"(ret)
		:[SYS_NUM] "0"(SYSGETPID)
		:"eax"
	);


	// __asm__ __volatile__ ("movl %0, %%eax;" ::"I"(SYSGETPID):"eax");
	// __asm__ __volatile__ ("int $46;" :"=m"(ret)::"eax");
	// __asm__ __volatile__ ("movl %%eax, %0;":"=m"(ret)::"memory");

	// __asm__ __volatile__ ("nop");
	// kprintf("[DEBUG] ++> ret : %u\n", ret);
	return ret;
}
