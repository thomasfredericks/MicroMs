#ifndef __MICRO_MS_H__
#define __MICRO_MS_H__

#include <Arduino.h>

// PUBLIC
// ----------------------------------------------------------------

class MicroMsChronometer
{
private:
    unsigned long _start;  
    public:
    unsigned long getElapsed() {
        return millis() - _start;
    }
    void add(unsigned long delta) {
        _start += delta;
    }
    void restart()
    {
        _start = millis();
    }
};


class MicroMsInterval : MicroMsChronometer
{
private:
    unsigned long  _interval;


public:
    MicroMsInterval(unsigned long  interval)
        : _interval(interval) {}

    bool triggered()
    {
        if (getElapsed() >= _interval)
        {
            // Drift-corrected update
            add(_interval);
            return true;
        }
        return false;
    }

};


// PRIVATE
// ----------------------------------------------------------------
#define MICRO_MS_CONCAT_(a, b) a##b
#define MICRO_MS_CONCAT(a, b) MICRO_MS_CONCAT_(a, b)


#define MICRO_MS_INTSTANTIATE_LOOP_FOR(name,duration) static unsigned long name = millis(); \
    while (millis() - name < duration )

#define MICRO_MS_INTSTANTIATE_EVERY(name,interval) static MicroMsInterval name(interval); \
    if (name.triggered())

// PUBLIC
// ----------------------------------------------------------------

#define MICRO_MS_EVERY(interval) MICRO_MS_INTSTANTIATE_EVERY( MICRO_MS_CONCAT(_micro_ms_, __COUNTER__), interval)                                                       \

#define MICRO_MS_LOOP_FOR(duration)  MICRO_MS_INTSTANTIATE_LOOP_FOR( MICRO_MS_CONCAT(_micro_ms_, __COUNTER__), duration)                                                       \

#endif // __MICROMS_H__
