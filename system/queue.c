/* queue.c - enqueue, dequeue */

#include <xinu.h>

struct qentry	queuetab[NQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	enqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	qid16	tail, prev;		/* Tail & previous node indexes	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	tail = queuetail(q);
	prev = queuetab[tail].qprev;

	queuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	queuetab[pid].qprev  = prev;
	queuetab[prev].qnext = pid;
	queuetab[tail].qprev = pid;
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	dequeue(
	  qid16		q		/* ID of queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (isbadqid(q)) {
		return SYSERR;
	} else if (isempty(q)) {
		return EMPTY;
	}

	pid = getfirst(q);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	lottery(
	  qid16		q		/* ID of queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (isbadqid(q)) {
		return SYSERR;
	} else if (isempty(q)) {
		return EMPTY;
	}

	// counter: used to track if we’ve found the winner yet 
	uint32 counter = 0;
	uint32 totaltickets=0;
	pid32 walkq=firstid(q);
	while(walkq!=queuetail(q)){
		totaltickets+=queuetab[walkq].qtickets;
		walkq=queuetab[walkq].qnext;
	}
	// winner: use some call to a random number generator to 
	// get a value, between 0 and the total # of tickets 
	if(totaltickets==0){
		kprintf("totaltickets is 0!!\n");
		totaltickets=1;
	}
	kprintf("totaltickets : %d\n",totaltickets);
	uint32 winner = rand()% totaltickets;
	// current: use this to walk through the list of jobs 
	kprintf("winner : %d\n",winner);
	pid32	curr = firstid(q); 
	while (curr!=0) 
	{
		counter = counter + proctab[curr].tickets; 
		if (counter > winner)
			break; // found the winner 
		curr = queuetab[curr].qnext;
	}
	// ’current’ is the winner: schedule it...		
	kprintf("curr: %d",curr);
	pid = getitem(curr);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;

	return pid;
}
