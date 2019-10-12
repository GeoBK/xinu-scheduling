/* wakeup.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */

	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		pid32 pidd=dequeue(sleepq);
		kprintf("Process being woken up: %d",pidd);
		ready(pidd);
		print_ready_list();
	}

	resched_cntl(DEFER_STOP);
	return;
}
