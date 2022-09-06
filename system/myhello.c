#include <xinu.h>

void myhello(void) {
    kprintf("\nHello World!\n");
    kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
    kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
    kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
    kprintf("\nName : Muhammad Bilal Naeem\n");
    kprintf("\nUsername : naeem3\n");
    return;    
}
