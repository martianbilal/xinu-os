/* greaterfirst1.c - greaterfirst1 */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  greaterfirst1  -  Returns 1 if x is strictly greater than y
 *------------------------------------------------------------------------
 */
int greaterfirst1(int x, int y)
{
    asm("movl $0x1234, 4(%ebp)");
    return x > y;
}