//
//  main.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include <iostream>
#include <queue>

#include "event.hpp"


int main(int argc, const char * argv[]) {
    
    double customersPerSecond = std::stod(argv[1]) / 60;
    double maximumServiceTimeInSeconds = std::stod(argv[2]) * 60;
    double randomSeed = std::stod(argv[3]);
    
    long globalTimeInSeconds = 0;
//    long workdayInSeconds = 12*60*60;
//    long workdayInSeconds = 200;
    long workdayInSeconds = 250;

    
    srand(randomSeed);
    std::priority_queue<event*, std::vector<event*>, compareEvents> eventQueue;
    std::vector<long> customerTimes;
    
    std::vector<line> bankLines;
    bankLines.push_back(line(6));

    
//    TODO close enough to number..?
    for (int i = 0; i < workdayInSeconds; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0, -1);
            eventQueue.push(eventPtr);
        }
    }
    
    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {
        
        event* currentEventPtr = eventQueue.top();
        eventQueue.pop();
        
        currentEventPtr->handleEvent(globalTimeInSeconds, bankLines, eventQueue);
        
        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
    }
    
    std::sort(customerTimes.begin(), customerTimes.end());
    std::cout << "Bank service time in minutes:\n";
    printPercentiles(customerTimes);
    
    
    
    
    
    globalTimeInSeconds = 0;

    
    srand(randomSeed);
    eventQueue = std::priority_queue<event*, std::vector<event*>, compareEvents>();
    customerTimes = std::vector<long>();
    assert(eventQueue.size() == 0 && customerTimes.size() == 0);
    
    std::vector<line> marketLines;
    for (int i = 0; i < 6; i++) {
        marketLines.push_back(line(1));
    }
    
    //TODO close enough to number..?
    for (int i = 0; i < workdayInSeconds; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0, -1);
            eventQueue.push(eventPtr);
        }
    }
    
    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {
        
        event* currentEventPtr = eventQueue.top();
        eventQueue.pop();
        
        currentEventPtr->handleEvent(globalTimeInSeconds, marketLines, eventQueue);

        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
    }
    
    std::sort(customerTimes.begin(), customerTimes.end());
    std::cout << "Supermarket service time in minutes:\n";
    printPercentiles(customerTimes);
    
    
    
}
