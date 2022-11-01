/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */

	.data
	.globl 	stkfrmdisp 	# Stack frame dispatcher 
stkfrmdisp:	.space 4	# 4 bytes for stack frame dispatcher 
	.long 	stkfrmdisp

#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
clkdisp:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler
		# push 40(%esp)	
		# # eflags
		# push 36(%esp)	
		# # cs
		# push 32(%esp)	
		# eip
		# 
		call	executedetour	# Return from interrupt
		sti			# Restore interrupt status
		popal			# Restore registers
		iret			# Return from interrupt
