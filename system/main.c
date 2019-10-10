/*  main.c  - main */

#include <xinu.h>

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

void sync_printf(char *fmt, ...)
{
    	intmask mask = disable();
	void *arg = __builtin_apply_args();
	__builtin_apply((void*)kprintf, arg, 100);
	restore(mask);
}
void test1(uint32 a){
	printf("test1 : %d\n",a);
}
process	main(void)
{    
	print_ready_list();	
	pid32 pid1=create_user_process((void *)test1, 8192, "test1", 1, 123);
	resume(pid1);
	burst_execution(1,10,10);
	return OK;
    
}
