#include <xinu.h>

void burst_execution(uint32 number_bursts, uint32 burst_duration, uint32 sleep_duration)
{
    int i;
    for(i=0;i<number_bursts;i++)
    {
        int stime = ctr1000;
        while((ctr1000-stime)<burst_duration);
        sleepms(sleep_duration);
    }

} 