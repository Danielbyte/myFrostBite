#include "../Header-files/stopwatch.h"

Stopwatch::Stopwatch() :
	final_time{ 0.0f }
{
	initial_time = current_time();
}

float Stopwatch::current_time()
{
	auto time = clock();
	return static_cast<float>(time) / CLOCKS_PER_SEC;
}

float Stopwatch::elapsed_time()
{
	stop_timer();
	auto elapsedTime = final_time - initial_time;
	return elapsedTime;
}

void Stopwatch::stop_timer()
{
	final_time = current_time();
}

void Stopwatch::restart_timer()
{
	initial_time = current_time();
}

