//
//  event.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "event.hpp"

event::event(long inputEventTime, long inputServiceTime, long inputTimeTaken, long inputLine) {
    eventTime = inputEventTime;
    serviceTime = inputServiceTime;
    timeTaken = inputTimeTaken;
    lineNumber = inputLine;
}

long event::getTimeTaken(){
    return timeTaken;
}


void event::handleEvent(long &globalTime, std::vector<line> &lines, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue) {
    assert(false);
}

long event::getEventTime(){
    return eventTime;
}


void newPersonEvent::handleEvent(long &globalTime, std::vector<line> &lines, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue) {

    for (line l : lines) {
        l.syncLine(eventTime-globalTime);
    }
    globalTime = eventTime;
    
    lineNumber = determineLine(lines);
    
    if (lines[lineNumber].getRegister() > 0) {
        lines[lineNumber].setRegister(-1);
        tellerFreedEvent* eventPtr = new tellerFreedEvent(globalTime+serviceTime, serviceTime, serviceTime, lineNumber);
        eventQueue.push(eventPtr);
    } else {
        lines[lineNumber].addCustomer(customer(eventTime, serviceTime));
    }
}




void tellerFreedEvent::handleEvent(long &globalTime, std::vector<line> &lines, std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue) {
    
    for (line l : lines) {
        l.syncLine(eventTime-globalTime);
    }
    globalTime = eventTime;
    
    if (lines[lineNumber].getCustomerQueueSize() == 0) {
        lines[lineNumber].setRegister(1);
    } else {
        //Replace the orginal codes with calling removeCustomer function
        customer currentCustomer = lines[lineNumber].removeCustomer();
        if(currentCustomer.getArrivalTime() == -1 && currentCustomer.getTimeNeeded() == -1) return;
        tellerFreedEvent* eventPtr = new tellerFreedEvent(globalTime+currentCustomer.getTimeNeeded(), serviceTime, globalTime-currentCustomer.getArrivalTime()+serviceTime, lineNumber);
        eventQueue.push(eventPtr);
    }
}


bool compareEvents::operator()(event* rhs, event* lhs) {
    return rhs->getEventTime() > lhs->getEventTime();
}



int determineLine(std::vector<line> lines) {
    long lowTime = lines[0].getTotalLineTime();
    int index = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].getRegister() > 0) {
            return i;
        }
    }
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].getTotalLineTime() < lowTime) {
            lowTime = lines[i].getTotalLineTime();
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
    
    std::cout << "10th percenile " << tenthPercentile << "\n50th percentile " << fiftiethPercentile << "\n90th percentile " << nintiethPercentile << "\n\n";
    std::cout << nintiethPercentile << "\n";

    //return nintiethPercentile;
}
