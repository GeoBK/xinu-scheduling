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
// 	//kprintf("1\n");
// 	receive();
// 	kprintf("2\n");
// 	//print_ready_list();
// 	receive();
// 	//kprintf("3\n");
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




// #include <xinu.h>
// #include <stdio.h>

// void sync_printf(char *fmt, ...)
// {
//         intmask mask = disable();
//         void *arg = __builtin_apply_args();
//         __builtin_apply((void*)kprintf, arg, 100);
//         restore(mask);
// }

// int main() {
// 	pid32 prA, prB;

// 	sync_printf("\n");
// 	sync_printf("=== TESTCASE 1:: 1 process with burst execution - context switches ======\n");	
// 	prA = create_user_process(burst_execution, 1024, "burst_execution", 3, 4, 40, 40);
// 	set_tickets(prA, 50);
// 	resume(prA);
// 	receive();
// 	sleepms(20); //wait for user process to terminate	
// 	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
// 	sync_printf("=========================================================================\n\n");	

// 	sync_printf("=== TESTCASE 2::  2 processes with burst execution - context switches ===\n");	
// 	prA = create_user_process(burst_execution, 1024, "burst_execution", 3, 4, 40, 40);
// 	prB = create_user_process(burst_execution, 1024, "burst_execution", 3, 4, 40, 40);
// 	set_tickets(prA, 90);
// 	set_tickets(prB, 10);
// 	resume(prA);
// 	resume(prB);
// 	receive();
// 	receive();
// 	sleepms(50); //wait for user processes to terminate	
// 	kprintf("\nprocess %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
// 	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
// 	sync_printf("=========================================================================\n\n");	
	
// 	return OK;
// }



// #include <xinu.h>
// #include <stdio.h>

// pid32 prA, prB, prC, prD;
// uint32 a_cnt, b_cnt, c_cnt, d_cnt;

// void compute(uint32 runtime, uint32 *value)
// {   
//         int i;
//         while (proctab[currpid].runtime<runtime) {
//             for (i = 0; i < 1000; i++)
//                 ;
//             (*value)++;
//         }
// }

// int main() {

// 	double total_cnt, a_percent, b_percent, c_percent, d_percent;
	
// 	a_cnt = b_cnt = c_cnt = d_cnt = 0;	
	
// 	kprintf("\n\n================= TESTCASE 1: 2 processes ======================\n");
// 	total_cnt=0;
// 	a_percent=0;
// 	b_percent=0;
// 	prA = create_user_process(compute, 1024, "process A", 2, 10000, &a_cnt);
// 	prB = create_user_process(compute, 1024, "process B", 2, 10000, &b_cnt);
// 	set_tickets(prA, 1000);
// 	set_tickets(prB, 1000);
// 	resume(prA);
// 	resume(prB);
// 	sleepms(4000);
// 	kill(prA);
// 	kill(prB);
// 	total_cnt = a_cnt + b_cnt ;
// 	a_percent = (double) a_cnt / total_cnt * 100;
// 	b_percent = (double) b_cnt / total_cnt * 100;
// 	kprintf("Test RESULT: A : B (%d : %d)\n", (int) a_percent, (int) b_percent);

	
// 	a_cnt = b_cnt = c_cnt = d_cnt = 0;	
// 	kprintf("\n\n================= TESTCASE 2: 2 processes ======================\n");
// 	total_cnt=0;
// 	a_percent=0;
// 	b_percent=0;
// 	prA = create_user_process(compute, 1024, "process A", 2, 10000, &a_cnt);
// 	prB = create_user_process(compute, 1024, "process B", 2, 10000, &b_cnt);
// 	set_tickets(prA, 1000);
// 	set_tickets(prB, 0);
// 	resume(prA);
// 	resume(prB);
// 	sleepms(4000);
// 	kill(prA);
// 	kill(prB);
// 	total_cnt = a_cnt + b_cnt ;
// 	a_percent = (double) a_cnt / total_cnt * 100;
// 	b_percent = (double) b_cnt / total_cnt * 100;
// 	kprintf("Test RESULT: A : B (%d : %d)\n", (int) a_percent, (int) b_percent);
 
	
// 	a_cnt = b_cnt = c_cnt = d_cnt = 0;	
// 	kprintf("\n\n================= TESTCASE 3: 2 processes ======================\n");
// 	total_cnt=0;
// 	a_percent=0;
// 	b_percent=0;
// 	prA = create_user_process(compute, 1024, "process A", 2, 10000, &a_cnt);
// 	prB = create_user_process(compute, 1024, "process B", 2, 1000, &b_cnt);
// 	set_tickets(prA, 1000);
// 	set_tickets(prB, 1000);
// 	resume(prA);
// 	resume(prB);
// 	sleepms(4000);
// 	kill(prA);
// 	kill(prB);
// 	total_cnt = a_cnt + b_cnt ;
// 	a_percent = (double) a_cnt / total_cnt * 100;
// 	b_percent = (double) b_cnt / total_cnt * 100;
// 	kprintf("Test RESULT: A : B (%d : %d)\n", (int) a_percent, (int) b_percent);

	
// 	a_cnt = b_cnt = c_cnt = d_cnt = 0;	
// 	kprintf("\n\n================= TESTCASE 4: 4 processes ======================\n");
// 	total_cnt=0;
// 	a_percent=0;
// 	b_percent=0;
// 	a_cnt=b_cnt=0;
// 	prA = create_user_process(compute, 1024, "process A", 2, 10000, &a_cnt);
// 	prB = create_user_process(compute, 1024, "process B", 2, 10000, &b_cnt);
// 	prC = create_user_process(compute, 1024, "process C", 2, 10000, &c_cnt);
// 	prD = create_user_process(compute, 1024, "process D", 2, 10000, &d_cnt);
// 	set_tickets(prA, 2000);
// 	set_tickets(prB, 1000);
// 	set_tickets(prC, 500);
// 	set_tickets(prD, 250);
// 	resume(prA);
// 	resume(prB);
// 	resume(prC);
// 	resume(prD);
// 	sleepms(8000);
// 	kill(prA);
// 	kill(prB);
// 	kill(prC);
// 	kill(prD);
// 	total_cnt = a_cnt + b_cnt + c_cnt + d_cnt;
// 	a_percent = (double) a_cnt / total_cnt * 100;
// 	b_percent = (double) b_cnt / total_cnt * 100;
// 	c_percent = (double) c_cnt / total_cnt * 100;
// 	d_percent = (double) d_cnt / total_cnt * 100;
// 	kprintf("Test RESULT: A : B : C : D (%d : %d : %d : %d)\n",
// 	        (int) a_percent, (int) b_percent, (int) c_percent, (int) d_percent);


// 	a_cnt = b_cnt = c_cnt = d_cnt = 0;	
// 	kprintf("\n\n================= TESTCASE 5: 4 processes ======================\n");
// 	total_cnt=0;
// 	a_percent=0;
// 	b_percent=0;
// 	a_cnt=b_cnt=0;
// 	prA = create_user_process(compute, 1024, "process A", 2, 10000, &a_cnt);
// 	prB = create_user_process(compute, 1024, "process B", 2, 10000, &b_cnt);
// 	set_tickets(prA, 1000);
// 	set_tickets(prB, 1000);
// 	resume(prA);
// 	resume(prB);
// 	sleepms(4000);
// 	prC = create_user_process(compute, 1024, "process C", 2, 10000, &c_cnt);
// 	prD = create_user_process(compute, 1024, "process D", 2, 10000, &d_cnt);
// 	set_tickets(prC, 1000);
// 	set_tickets(prD, 1000);
// 	resume(prC);
// 	resume(prD);
// 	sleepms(4000);
// 	kill(prC);
// 	kill(prD);
// 	total_cnt = a_cnt + b_cnt + c_cnt + d_cnt;
// 	a_percent = (double) a_cnt / total_cnt * 100;
// 	b_percent = (double) b_cnt / total_cnt * 100;
// 	c_percent = (double) c_cnt / total_cnt * 100;
// 	d_percent = (double) d_cnt / total_cnt * 100;
// 	kprintf("Test RESULT: A : B : C : D (%d : %d : %d : %d)\n",
// 	        (int) a_percent, (int) b_percent, (int) c_percent, (int) d_percent);

// 	return OK;
// }










#include <xinu.h>
#include <stdio.h>

void timed_execution(uint32 runtime){
	    while(proctab[currpid].runtime<runtime);
}

int main() {
	pid32 prA, prB, prC, prD;

	kprintf("\n");
	
	kprintf("=== TESTCASE 1::  CPU-intensive jobs =============================\n");

	prA = create_user_process(timed_execution, 1024, "timed_execution", 1, 10000);
	prB = create_user_process(timed_execution, 1024, "timed_execution", 1, 10000);
	prC = create_user_process(timed_execution, 1024, "timed_execution", 1, 10000);

	set_tickets(prA, 50);
	set_tickets(prB, 50);
	set_tickets(prC, 0);

	
	
	resume(prA);
	resume(prB);
	resume(prC);
	// print_ready_list();
	receive();	
	receive();	

	sleepms(50); // wait for user processes to terminate	

	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prC, proctab[prC].runtime, proctab[prC].turnaroundtime, proctab[prC].num_ctxsw);

	set_tickets(prC,1);
	
	receive();	
   
	sleepms(20); // wait for user processes to terminate	
 
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prC, proctab[prC].runtime, proctab[prC].turnaroundtime, proctab[prC].num_ctxsw);

	prD = create_user_process(timed_execution, 1024, "timed_execution", 1, 10000);
	set_tickets(prD,1);
	resume(prD);
	
	receive();	
	
	sleepms(20); // wait for user processes to terminate	
	
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prD, proctab[prD].runtime, proctab[prD].turnaroundtime, proctab[prD].num_ctxsw);

	kprintf("==================================================================\n\n");

	kprintf("=== TESTCASE 2::  interactive jobs ===============================\n");

	prA = create_user_process(burst_execution, 1024, "burst_execution", 3, 10, 500, 500);
	prB = create_user_process(burst_execution, 1024, "burst_execution", 3, 10, 500, 500);
	prC = create_user_process(burst_execution, 1024, "burst_execution", 3, 10, 500, 500);

	set_tickets(prA, 800);
	set_tickets(prB, 100);
	set_tickets(prC, 100);
	
	resume(prA);
	resume(prB);
	resume(prC);

	receive();
	print_ready_list();	
	receive();	
	print_ready_list();	
	receive();	

	sleepms(50); // wait for user processes to terminate	

	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
	kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prC, proctab[prC].runtime, proctab[prC].turnaroundtime, proctab[prC].num_ctxsw);

	kprintf("==================================================================\n\n");

	return OK;
}
// void run_for_time(int t)
// {	
// 	while(ctr1000-proctab[currpid].prcreatetime<t);
// }

// int main(){
// 	kprintf("\n");
// 	kprintf("=== TESTCASE 1::  CPU-intensive jobs =============================\n");
// 	pid32 prA, prB;
// 	int runtime;
// 	for(runtime=0;runtime<50000;runtime+=1000)
// 	{
// 		prA = create_user_process(run_for_time, 1024, "timed_execution", 1, runtime);
// 		prB = create_user_process(run_for_time, 1024, "timed_execution", 1, runtime);	

// 		set_tickets(prA, 500);
// 		set_tickets(prB, 500);	
		
// 		resume(prA);
// 		resume(prB);
		
// 		receive();	
// 		receive();	

// 		sleepms(50); // wait for user processes to terminate	

// 		//kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prA, proctab[prA].runtime, proctab[prA].turnaroundtime, proctab[prA].num_ctxsw);
// 		//kprintf("process %d:: runtime=%d, turnaround time=%d, ctx=%d\n",prB, proctab[prB].runtime, proctab[prB].turnaroundtime, proctab[prB].num_ctxsw);
		
// 		kprintf("%0.4f\n",(float)proctab[prA].runtime/(float)proctab[prB].runtime);
// 	}
// 	return OK;
	


// }

