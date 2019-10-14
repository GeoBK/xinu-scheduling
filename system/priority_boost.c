//priority_boost.c - implements priority_boost() which periodically increases the priority 
//  of all user processes in the system.
#include <xinu.h>

void priority_boost()
{
    // kprintf("Inside priority boost!!!--------------------------------------------------------------\n");
    int i=0;
    //set to highest priority in PCB table
    for(i=1;i<NPROC;i++)
    {
        if(proctab[i].prstate != PR_FREE && proctab[i].isuserprocess == 1)
        {
            proctab[i].mlfqpriority=3;
            proctab[i].tatracker=0;
            preemptmlfq=0;
        }
    }

    //set to highest priority in readylist
    pid32 walkq;
    for(walkq=firstid(readylist);walkq!=0;walkq=queuetab[walkq].qnext)
    {
        if(queuetab[walkq].isuserprocess==1)
        {
            queuetab[walkq].mlfqpriority=3;
        }
    }

    resched();
}

