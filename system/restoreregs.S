/* retoreregs.s - restore (x86) */

/*------------------------------------------------------------------------
 * restore  - restore the register values from the stack
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	restoreregs		# Clock interrupt dispatcher
restoreregs:
		movl %ebp, %esp
		popl %ebp
		popl %ebx
		

		popal			# Restore registers
		iret			# Return from interrupt
