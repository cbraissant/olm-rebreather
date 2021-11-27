/*
 * @ author Alexander Brevig
 * Provide an easy way of triggering functions at a set interval
 */

#ifndef TIMEDACTION_H
#define TIMEDACTION_H

#include <Arduino.h>

class TimedAction {
   public:
    TimedAction(unsigned long interval, void (*function)());

    void reset();
    void disable();
    void enable();
    void check();
    void setInterval();

   private:
    bool active;
    unsigned long previous;
    unsigned long interval;
    void (*execute)();
};

#endif