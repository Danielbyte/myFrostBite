#include "../Header-files/stopwatch.h"

Stopwatch::Stopwatch() :
	final_time{}
{
	initial_time = current_time();
}

std::chrono::time_point<std::chrono::high_resolution_clock> Stopwatch::current_time()
{
	auto time = std::chrono::high_resolution_clock::now();
	return time;
	//return (static_cast<float>(time) / CLOCKS_PER_SEC);
}

float Stopwatch::elapsed_time()
{
	stop_timer();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(final_time-initial_time);
	auto TimePassed = static_cast<float> (elapsedTime.count())/1000000.0f;
	return TimePassed;
}

void Stopwatch::stop_timer()
{
	final_time = current_time();
}

void Stopwatch::restart_timer()
{
	initial_time = current_time();
}

