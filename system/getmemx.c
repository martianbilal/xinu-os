/* getmemx.c - getmemx */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmemx  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char  	*getmemx(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	char* ret=0;
	kprintf("====> getmemx called with {%u} bytes", (uint32)nbytes);


	// __asm__ volatile (
	// 	"int $46;"
	// 	:"=am"((pid32)ret)
	// 	:"0"(SYSGETPID)
	// );

	__asm__ __volatile__ (
		"movl %[SYS_NUM], %%eax;"
		"movl %[bytes], %%ebx;"
		"pushl %%ebx;"
		"int $46;"
		"mov %%esi, %%eax;"
		"mov %%eax, %[retval];"
		"popl %%ebx"
		:[retval] "=rm"(ret)
		:[SYS_NUM] "0"(SYSMEMGET), [bytes] "rm"((uint32)nbytes)
		:"eax"
	);


	// __asm__ __volatile__ ("movl %0, %%eax;" ::"I"(SYSGETPID):"eax");
	// __asm__ __volatile__ ("int $46;" :"=m"(ret)::"eax");
	// __asm__ __volatile__ ("movl %%eax, %0;":"=m"(ret)::"memory");

	// __asm__ __volatile__ ("nop");
	kprintf("[DEBUG] [getmemx] ++> ret : %u\n", ret);
	return ret;
}
