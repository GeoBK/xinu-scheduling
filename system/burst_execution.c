#include <xinu.h>

void burst_execution(uint32 number_bursts, uint32 burst_duration, uint32 sleep_duration)
{
    int i;
    for(i=1;i<=number_bursts;i++)
    {
        while(proctab[currpid].runtime<(i*burst_duration));
        sleepms(sleep_duration);
    }

} 