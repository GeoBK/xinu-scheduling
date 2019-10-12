/* resched.c - resched, resched_cntl */


#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	//kprintf("Inside resched!");

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];
	pid32	oldpid=currpid;

	
	
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			//kprintf("return \n");			
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio, ptold->isuserprocess, ctr1000 - ptold->runstime);
	}
	ptold->runtime += ctr1000 - ptold->runstime;

	print_ready_list();
	
	/* Force context switch to highest priority ready process */	
	currpid = dequeue(readylist);
	
	
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;	
	ptnew->runstime = ctr1000;

	if(ptnew->isuserprocess==1){
		if(queuetab[currpid].mlfqpriority==3)
		{
			preempt=QUANTUM;
		}else if(queuetab[currpid].mlfqpriority==2)
		{
			preempt=QUANTUM*2;
		}else if(queuetab[currpid].mlfqpriority==1){
			preempt=QUANTUM*4;
		}		
		//kprintf("preempt after scheduling: %d\n",preempt);
	}else{
		preempt = QUANTUM;
	}	

	if(oldpid!=currpid){
		(ptnew->num_ctxsw)++;		
	}
	#define DEBUG_CTXSW
	#ifdef DEBUG_CTXSW  
	if(oldpid!=currpid){		
		kprintf("ctxsw::%d-%d\n",oldpid,currpid);
	}	
	#endif
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
