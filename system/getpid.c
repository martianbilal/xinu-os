/* getpid.c - getpid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpid  -  Return the ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid32	getpid(void)
{
	kprintf("======getpid called=====\n");
	kprintf("currpid\t:\t%d\n", currpid);
	return (currpid);
}
