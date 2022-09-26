/* getpidx.c - getpidx */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpidx  -  Return the ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid32	getpidx(void)
{
	return (currpid);
}
