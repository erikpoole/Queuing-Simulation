//
//  event.hpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include <stdio.h>

#include <iostream>
#include <queue>
#include <vector>

#endif /* event_hpp */

class compareEvents;

class event {
public:
    long eventTime;
    long serviceTime;
    long timeTaken;
    
    event(long inputEventTime, long inputServiceTime, long inputTotalTime);
    
    virtual void handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters);
};

class newPersonEvent : public event {
public:
    using event::event;
    
    void handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters);
};

class tellerFreedEvent : public event {
public:
    using event::event;
    
    void handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters);
};




class compareEvents {
public:
    bool operator()(event* rhs, event* lhs);
};


int determineLine(std::vector<long> lineTimes);

void printPercentiles(std::vector<long> inputVector);
