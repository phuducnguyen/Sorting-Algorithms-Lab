#ifndef TIMER_HEADER
#define TIMER_HEADER

#include <chrono>

class Timer {
private:
	std::chrono::high_resolution_clock::time_point last_time;
public:
	Timer();
	void start();
	int64_t getRunningTime();
};

Timer::Timer() {
	last_time = std::chrono::high_resolution_clock::now();
}

void Timer::start() {
	last_time = std::chrono::high_resolution_clock::now();
}

// Return in nanosecond
int64_t Timer::getRunningTimeNS() {
	auto current_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds> (current_time - last_time);
	return duration.count(); 
}

#endif