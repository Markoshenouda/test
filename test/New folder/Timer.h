/*
 * Timer.h
 *
 *  Created on: Jun 17, 2025
 *      Author: Mariam Samy
 */
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <fstream>
#include <string>
#include <iostream>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::string label;

public:
    Timer(const std::string& name) : label(name) {
        startTime = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        double seconds = duration.count() / 1e9;

        std::ofstream log("performance_log.txt", std::ios::app);
        log << label << ": " << seconds << " sec (" << duration.count() << " nsec)" << std::endl;
        log.close();

        std::cout << label << ": " << seconds << " sec (" << duration.count() << " nsec)" << std::endl;
    }
};

#endif




