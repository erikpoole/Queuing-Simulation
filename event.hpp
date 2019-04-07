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

#include "line.hpp"

#endif /* event_hpp */

class compareEvents;

class event {
public:
    long eventTime;
    long serviceTime;
    long timeTaken;
    long lineNumber;
    
    event(long inputEventTime, long inputServiceTime, long inputTimeTaken, long inputLine);
    
    virtual void handleEvent(long &globalTime, std::vector<line> &lines, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue);
};

class newPersonEvent : public event {
public:
    using event::event;
    
    void handleEvent(long &currentTime, std::vector<line> &lines, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue);
};

class tellerFreedEvent : public event {
public:
    using event::event;
    
    void handleEvent(long &currentTime, std::vector<line> &lines, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue);
};




class compareEvents {
public:
    bool operator()(event* rhs, event* lhs);
};


//int determineLine(std::vector<long> lineTimes);
int determineLine(std::vector<line> lineTimes);

void printPercentiles(std::vector<long> inputVector);
