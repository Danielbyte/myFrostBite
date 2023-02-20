#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

class Stopwatch
{
public:
	Stopwatch();
	float elapsed_time();
	void stop_timer();
	void restart_timer();

private:
	float current_time();
	float initial_time;
	float final_time;

};
#endif
