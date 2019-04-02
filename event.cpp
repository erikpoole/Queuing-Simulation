//
//  event.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "event.hpp"



event::event(long inputEventTime, long inputServiceTime, long inputTotalTime) {
    eventTime = inputEventTime;
    serviceTime = inputServiceTime;
    totalTime = inputTotalTime;
}

void event::handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters) {
    std::cout << "poop" << std::endl;
}

void newPersonEvent::handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters) {
    std::cout << "New Person\n";
    
    globalTime += eventTime;
    
    tellerFreedEvent* eventPtr = new tellerFreedEvent(serviceTime+totalLineTime, serviceTime, serviceTime+totalLineTime);
    eventQueue.push(eventPtr);
    if (freeRegisters > 0) {
        freeRegisters--;
    } else {
        lineTimes.push(serviceTime);
        totalLineTime += serviceTime;
    }
}

void tellerFreedEvent::handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters) {
    std::cout << "Teller Freed\n";
    
    if (lineTimes.size() == 0) {
        freeRegisters++;
    } else {
        totalLineTime -= lineTimes.front();
        lineTimes.pop();
    }
}



bool compareEvents::operator()(event* rhs, event* lhs) {
    return rhs->eventTime > lhs->eventTime;
}
