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
	insert(pid, readylist, prptr->prprio);
	resched();

	return OK;
}

syscall print_ready_list(){	
	int32 curr;
	printf("%u\n",queuetail(readylist));
	printf("%u\n",queuehead(readylist));
	printf("%u\n",firstid(readylist));
	printf("%u\n",lastid(readylist));
	// for (curr = firstid(readylist);queuetab[curr].qkey != queuetail(readylist);curr = queuetab[curr].qnext) {
	// 	printf("PID: %u \n",(unsigned int)curr);		
	// }
	return OK;
}
