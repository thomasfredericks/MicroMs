#ifndef __MICRO_MS_H__
#define __MICRO_MS_H__

#include <Arduino.h>

// PUBLIC
// ----------------------------------------------------------------

class MicroMsInterval
{
private:
    uint32_t interval;
    uint32_t lastMillis;

public:
    MicroMsInterval(uint32_t interval)
        : interval(interval), lastMillis(millis()) {}

    bool triggered()
    {
        uint32_t now = millis();
        if (now - lastMillis >= interval)
        {
            // Drift-corrected update
            lastMillis += interval;
            // Optional: catch up if system is slow
            if (now - lastMillis >= interval)
            {
                lastMillis = now;
            }
            return true;
        }
        return false;
    }

    void reset()
    {
        lastMillis = millis();
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
