//
//  event.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "event.hpp"

event::event(long inputEventTime, long inputServiceTime, long inputTimeTaken) {
    eventTime = inputEventTime;
    serviceTime = inputServiceTime;
    timeTaken = inputTimeTaken;
}


void event::handleEvent(long &globalTime, line &currentLine, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters) {
    assert(false);
}


void newPersonEvent::handleEvent(long &globalTime, line &currentLine, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters) {
    //    std::cout << "New Person\n";
    
    globalTime = eventTime;
    
    tellerFreedEvent* eventPtr = new tellerFreedEvent(globalTime+serviceTime+currentLine.totalLineTime, serviceTime, serviceTime+currentLine.totalLineTime);
    eventQueue.push(eventPtr);
    if (freeRegisters > 0) {
        freeRegisters--;
    } else {
        currentLine.addCustomer(serviceTime);
    }
}


void tellerFreedEvent::handleEvent(long &globalTime, line &currentLine, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue, int &freeRegisters) {
//    std::cout << "Teller Freed\n";
    
    globalTime = eventTime;
    
    if (currentLine.customersInLine.size() == 0) {
        freeRegisters++;
    } else {
        currentLine.removeCustomer();
    }
}

/*
 void line::addCustomer(long newCustomer) {
 customersInLine.push(newCustomer);
 totalLineTime += newCustomer;
 }
 
 void line::removeCustomer() {
 long leavingCustomer = customersInLine.front();
 customersInLine.pop();
 totalLineTime -= leavingCustomer;
 }
 */



bool compareEvents::operator()(event* rhs, event* lhs) {
    return rhs->eventTime > lhs->eventTime;
}



int determineLine(std::vector<line> lines) {
    long lowTime = lines[0].totalLineTime;
    int index = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].totalLineTime < lowTime) {
            lowTime = lines[i].totalLineTime;
            index = i;
        }
    }
    return index;
}


void printPercentiles(std::vector<long> inputVector) {
    
    
    double valuesPerPercentile = (double) inputVector.size() / 100;

    int tenthPercentileIndex = (int) 10*valuesPerPercentile;
    int fiftiethPercentileIndex = (int) 50*valuesPerPercentile;
    int nintiethPercentileIndex = (int) 90*valuesPerPercentile;
    
    double tenthPercentile = (double) inputVector[tenthPercentileIndex]/60;
    double fiftiethPercentile = (double) inputVector[fiftiethPercentileIndex]/60;
    double nintiethPercentile = (double) inputVector[nintiethPercentileIndex]/60;

//    std::cout << inputVector.size() << "\n";
//    std::cout << valuesPerPercentile << "\n";
//    std::cout << tenthPercentile << " " << tenthPercentileIndex << "\n";
//    std::cout << fiftiethPercentile << " " << fiftiethPercentileIndex << "\n";
//    std::cout << nintiethPercentile << " " << nintiethPercentileIndex << "\n";
    
    std::cout << "10th percenile " << tenthPercentile << "\n50th percentile " << fiftiethPercentile << "\n90th percentile " << nintiethPercentile << "\n\n";
}
