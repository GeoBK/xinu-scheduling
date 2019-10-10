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
	  uint32	tickets
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr = firstid(q);
	while (queuetab[curr].qkey >= key && (queuetab[curr].qkey !=0)) {
		curr = queuetab[curr].qnext;
	}

	//first time a ticket is inserted
	//number of tickets needs to be less than earlier if tickets are already present
	//
	// while ((queuetab[curr].qkey ==0) && (queuetab[curr].qtickets > tickets || (queuetab[curr].qtickets == tickets && (curr<pid && curr!=0)))){
		
	// 	curr = queuetab[curr].qnext;
	// }

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[pid].qtickets = tickets;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
