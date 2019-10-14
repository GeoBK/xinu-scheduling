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
	//kprintf("curr before loop: %d\n",curr);

	while (queuetab[curr].qkey >= key && (queuetab[curr].isuserprocess == 0 || pid==0) && curr!=0) 
	{
		//kprintf("old_curr:%d, priority: %d , new curr: %d, new key: %d",curr,queuetab[curr].qkey,pid,key);
		curr = queuetab[curr].qnext;
	}
	//kprintf("curr between loops: %d\n",curr);
	int mlfqpriority=0;
	if(isuserprocess==1)
	{		
		mlfqpriority=proctab[pid].mlfqpriority;
		while (queuetab[curr].mlfqpriority >= mlfqpriority){	
			//kprintf("inside for loop, curr: %d, curr priority %d, mlfqpriority: %d\n",curr, queuetab[curr].mlfqpriority, mlfqpriority);	
			curr = queuetab[curr].qnext;
		}
		
	}
	//kprintf("curr: %d\n",curr);
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
