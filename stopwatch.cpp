#include "stopwatch.h"

StopWatch::StopWatch() :
    started(false)
{
}

void StopWatch::start(void)
{
    started = true;
    clock_gettime(CLOCK_MONOTONIC, &starttime);
}

long StopWatch::elapsedmsec(void)
{
    if(!started) return -1;

    timespec tmp;
    clock_gettime(CLOCK_MONOTONIC, &tmp);
    tmp = timedifference(starttime,tmp);
    return tmp.tv_sec*1000+tmp.tv_nsec/1000000;
}

float StopWatch::elapsedsec(void)
{
    if(!started) return -1;

    timespec tmp;
    clock_gettime(CLOCK_MONOTONIC, &tmp);
    tmp = timedifference(starttime,tmp);
    return tmp.tv_sec + (float)tmp.tv_nsec/1000000000;
}

timespec StopWatch::timedifference(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}
