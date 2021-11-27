#include "TimedAction.h"

TimedAction::TimedAction(unsigned long interval, void (*function)()) {
    this->active = true;
    this->previous = 0;
    this->interval = interval;
    this->execute = function;
}

void TimedAction::reset() {
    previous = millis();
}

void TimedAction::disable() {
    this->active = false;
}

void TimedAction::enable() {
    this->active = true;
}

void TimedAction::check() {
    if (this->active && (millis() - previous >= interval)) {
        previous = millis();
        this->execute();
    }
}