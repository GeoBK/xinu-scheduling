/* create_user_process.c - create_user_process */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  create_user_process  -  Create a user process to start running a function on x86
 *------------------------------------------------------------------------
 */
 pid32	create_user_process(
	  void		*funcaddr,	/* Address of the function	*/
	  uint32	ssize,		/* Stack size in bytes		*/	  
	  char		*name,		/* Name (for debugging)		*/
	  uint32	nargs,		/* Number of args that follow	*/
	  ...
	)
{
    
    pri16       priority=1;
    // uint32		*a;		/* Points to list of args	*/
    // /* Push arguments */
	// a = (uint32 *)(&nargs + 1);	/* Start of args		*/
	// a += nargs -1;			/* Last argument		*/
    // asm()
	// for ( ; nargs > 0 ; nargs--)	/* Machine dependent; copy args	*/
	// 	*--saddr = *a--;	/* onto created process's stack	*/
	// *--saddr = (long)INITRET;	/* Push on return address	*/
	return create(funcaddr,ssize,priority,name,nargs);
}