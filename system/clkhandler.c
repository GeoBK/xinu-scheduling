/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	ctr1000++;
	proctab[currpid].runtime++;

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/
		//kprintf("head sleep counter : %d\n",queuetab[firstid(sleepq)].qkey);
		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			//kprintf("Wake up called \n");
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */
	//kprintf("cpreempt: %d\n",preempt);
	--preemptmlfq;
	if((--preempt) <= 0 ) {
		preempt = QUANTUM;		
		resched();
	}
	//kprintf("reset_counter: %d, preempt : %d\n", reset_counter,preempt);
	if((--reset_counter) <= 0)
	{
		reset_counter = PRIORITY_BOOST_PERIOD;
		priority_boost();
	}

}
