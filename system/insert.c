/* insert.c - insert */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key,		/* Key for the inserted process	*/
	  bool8		isuserprocess,
	  uint32	timeslicelength
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}
	//kprintf("Inside insert !\n");
	curr = firstid(q);

	while (queuetab[curr].qkey >= key && (queuetab[curr].isuserprocess == 0)) {
		curr = queuetab[curr].qnext;
	}
	int mlfqpriority=3;
	if(isuserprocess==1){
		proctab[pid].tatracker+=timeslicelength;
		if(proctab[pid].tatracker>TIME_ALLOTMENT)
		{
			proctab[pid].tatracker=0;
			if(proctab[pid].mlfqpriority!=1)
			{
				proctab[pid].mlfqpriority--;
			}
		}
		mlfqpriority=proctab[pid].mlfqpriority;
		while (queuetab[curr].mlfqpriority >= mlfqpriority){		
			curr = queuetab[curr].qnext;
		}
		
	}
	
	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[pid].isuserprocess = isuserprocess;
	queuetab[pid].mlfqpriority = mlfqpriority;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
