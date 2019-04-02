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
    long workdayInSeconds = 12*60*60;
    int registerCount = 6;
    
    srand(randomSeed);
    std::priority_queue<event*, std::vector<event*>, compareEvents> eventQueue;
    std::vector<long> customerTimes;
    
    line bankLine = line();

    
    //TODO close enough to number..?
    for (int i = 0; i < workdayInSeconds; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0);
            eventQueue.push(eventPtr);
        }
    }
    
    std::cout << "Customers: " << eventQueue.size() << "\n\n";
    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {

        event* currentEventPtr = eventQueue.top();
//        std::cout << eventQueue.top()->eventTime << "\n";
//        std::cout << "Registers: " << registerCount << " LineTime: " << lineTime << "\n";
//        std::cout << "Service Time: " << currentEventPtr->serviceTime << "\n";
        eventQueue.pop();
        currentEventPtr->handleEvent(globalTimeInSeconds, bankLine, eventQueue, registerCount);
        
        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
    }
    
//    for (long time : customerTimes) {
//        std::cout << time << "\n";
//    }
    
    std::sort(customerTimes.begin(), customerTimes.end());
    std::cout << "Bank service time in minutes:\n";
    printPercentiles(customerTimes);
    
    
    
    
    
    globalTimeInSeconds = 0;
    registerCount = 6;
    
    srand(randomSeed);
    eventQueue = std::priority_queue<event*, std::vector<event*>, compareEvents>();
    customerTimes = std::vector<long>();
    assert(eventQueue.size() == 0 && customerTimes.size() == 0);
    
    std::vector<line> marketLines(6);
    
    //TODO close enough to number..?
    for (int i = 0; i < workdayInSeconds; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0);
            eventQueue.push(eventPtr);
        }
    }
    
    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {
        
        event* currentEventPtr = eventQueue.top();
        //        std::cout << eventQueue.top()->eventTime << "\n";
        //        std::cout << "Registers: " << registerCount << " LineTime: " << lineTime << "\n";
        //        std::cout << "Service Time: " << currentEventPtr->serviceTime << "\n";
        eventQueue.pop();
        
        int lineIndex = determineLine(marketLines);
        currentEventPtr->handleEvent(globalTimeInSeconds, marketLines[lineIndex], eventQueue, registerCount);

        
        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
    }
    
    std::sort(customerTimes.begin(), customerTimes.end());
    std::cout << "Supermarket service time in minutes:\n";
    printPercentiles(customerTimes);
    
    
    
}
