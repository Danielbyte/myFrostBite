#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch
{
public:
	Stopwatch();
	float elapsed_time();
	void stop_timer();
	void restart_timer();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> current_time();
	std::chrono::time_point<std::chrono::high_resolution_clock> initial_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> final_time;

};
#endif
