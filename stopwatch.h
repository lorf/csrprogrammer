#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

class StopWatch
{
public:
    StopWatch();
    void start(void);
    long elapsedmsec(void);
    float elapsedsec(void);
private:
    timespec timedifference(timespec start, timespec end);
private:
    bool started;
    timespec starttime;
};

#endif // STOPWATCH_H
