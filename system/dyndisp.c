/* dyndisp.c - getquantum, gettqexp, getslpret */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getquantum  - get the quantum for a pid  
 *------------------------------------------------------------------------
 */
unsigned short getquantum(pri16 prio){
    if(prio < -1 || prio > 9) {
        return SYSERR;
    }

    if(prio == SYSERR) {
        // calculated using the formula in the lab manual
        // considering i to be -1
        return 110;
    }

    return dyndisp[prio].quantum;
}

/*------------------------------------------------------------------------
 *  gettqexp  - get the tqexp for a pid  
 *------------------------------------------------------------------------
 */
unsigned short gettqexp(pri16 prio){
    if(prio < 0 || prio > 9) {
        return SYSERR;
    }

    return dyndisp[prio].tqexp;
}

/*------------------------------------------------------------------------
 *  getslpret  - get the slpret for a pid  
 *------------------------------------------------------------------------
 */
unsigned short getslpret(pri16 prio){
    if(prio < 0 || prio > 9) {
        return SYSERR;
    }

    return dyndisp[prio].slpret;
}