/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	kprintf("pid: %d, readylist: %d, priority: %d, tickets: %d",pid, readylist, prptr->prprio, prptr->tickets);
	insert(pid, readylist, prptr->prprio, prptr->tickets);
	resched();

	return OK;
}

syscall print_ready_list(){	
	int32 curr;
	for (curr = firstid(readylist);curr != queuetail(readylist);curr = queuetab[curr].qnext) {
		printf("Ready List\n");
		printf("PID: %u \n",(unsigned int)curr);		
	}
	return OK;	
	
}
