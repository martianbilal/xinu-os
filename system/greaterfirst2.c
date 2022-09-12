/* greaterfirst2.c - greaterfirst2 */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  greaterfirst2 -  Returns 1 if x is strictly greater than y
 *------------------------------------------------------------------------
 */
int greaterfirst2(int x, int y)
{   
    /* using the information from testgreater stack */
    // asm("movl 28(%ebp), %eax");
    // asm("movl %eax, 4(%ebp)");
    
    /* using the saved ebp */
    asm("movl (%ebp), %eax");
    asm("movl 4(%eax), %eax");
    
    asm("movl %eax, 4(%ebp)");
    return x > y;
}