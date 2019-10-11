/*  main.c  - main */

// #include <xinu.h>

// process	main(void)
// {

// 	/* Run the Xinu shell */

// 	recvclr();
// 	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

// 	/* Wait for shell to exit and recreate it */

// 	while (TRUE) {
// 		receive();
// 		sleepms(200);
// 		kprintf("\n\nMain process recreating shell\n\n");
// 		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
// 	}
// 	return OK;
    
// }

// void sync_printf(char *fmt, ...)
// {
//     	intmask mask = disable();
// 	void *arg = __builtin_apply_args();
// 	__builtin_apply((void*)kprintf, arg, 100);
// 	restore(mask);
// }
// void test1(uint32 a){
// 	printf("test1 : %d\n",a);
// }
// process	main(void)
// {    
	
// 	pid32 pid1=create_user_process((void *)test1, 8192, "test1", 1, 123);	
// 	resume(pid1);
// 	print_ready_list();	
// 	set_tickets(pid1,50);	
// 	//burst_execution(1,10,10);
// 	return OK;
    
// }




// #include <xinu.h>
// #include <stdio.h>

// void timed_execution(uint32 runtime){
// 	    while(proctab[currpid].runtime<runtime);
// }

// void sync_printf(char *fmt, ...)
// {
//         intmask mask = disable();
//         void *arg = __builtin_apply_args();
//         __builtin_apply((void*)kprintf, arg, 100);
//         restore(mask);
// }

// int main() {
// 	pid32 prA, prB, prC;

// 	sync_printf("\n");

// 	sync_printf("=== TESTCASE 1::  1 process - context switches =================\n");	
// 	prA = create_user_process(timed_execution, 1024, "timed_execution", 1, 100);
// 	set_tickets(prA, 50);
// 	resume(prA);
// 	receive();
// 	sleepms(50); //wait for user process to terminate	
// 	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
	
// 	sync_printf("================================================================\n\n");	
// 	sync_printf("=== TESTCASE 2::  2 processes - context switches ===============\n");	
// 	prA = create_user_process(timed_execution, 1024, "timed_execution", 1, 100);
// 	prB = create_user_process(timed_execution, 1024, "timed_execution", 1, 100);
// 	set_tickets(prA, 50);
// 	set_tickets(prB, 50);
// 	resume(prA);
// 	resume(prB);
// 	kprintf("1\n");
// 	receive();
// 	kprintf("2\n");
// 	print_ready_list();
// 	receive();
// 	kprintf("3\n");
// 	sleepms(50); //wait for user processes to terminate	
// 	kprintf("4\n");
// 	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
//         kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
	
// 	sync_printf("================================================================\n\n");	

// 	sync_printf("=== TESTCASE 3::  3 processes - context switches ===============\n");	
// 	prA = create_user_process(timed_execution, 1024, "timed_execution", 1, 100);
// 	prB = create_user_process(timed_execution, 1024, "timed_execution", 1, 100);
// 	prC = create_user_process(timed_execution, 1024, "timed_execution", 1, 40);
// 	set_tickets(prA, 50);
// 	set_tickets(prB, 50);
// 	set_tickets(prC, 50);
// 	resume(prA);
// 	resume(prB);
// 	sleepms(50);	
// 	resume(prC);
// 	receive();
// 	receive();
// 	receive();
// 	sleepms(50); //wait for user processes to terminate	
// 	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
//         kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
//         kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prC, proctab[prC].runtime, proctab[prC].turnaroundtime, proctab[prC].num_ctxsw);
// 	sync_printf("================================================================\n\n");	
// 	return OK;
// }




#include <xinu.h>
#include <stdio.h>

void sync_printf(char *fmt, ...)
{
        intmask mask = disable();
        void *arg = __builtin_apply_args();
        __builtin_apply((void*)kprintf, arg, 100);
        restore(mask);
}

int main() {
	pid32 prA, prB;

	sync_printf("\n");
	sync_printf("=== TESTCASE 1:: 1 process with burst execution - context switches ======\n");	
	prA = create_user_process(burst_execution, 1024, "burst_execution", 3, 4, 40, 40);
	set_tickets(prA, 50);
	resume(prA);
	receive();
	sleepms(20); //wait for user process to terminate	
	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
	sync_printf("=========================================================================\n\n");	

	sync_printf("=== TESTCASE 2::  2 processes with burst execution - context switches ===\n");	
	prA = create_user_process(burst_execution, 1024, "burst_execution", 3, 4, 40, 40);
	prB = create_user_process(burst_execution, 1024, "burst_execution", 3, 4, 40, 40);
	set_tickets(prA, 90);
	set_tickets(prB, 10);
	resume(prA);
	resume(prB);
	receive();
	receive();
	sleepms(50); //wait for user processes to terminate	
	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
	sync_printf("=========================================================================\n\n");	
	
	return OK;
}
