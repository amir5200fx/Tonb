#include <Global_Timer.hxx>

float tnbLib::global_time_duration(0);

void tnbLib::Global_Timer::EstimateDuration()
{
	theEnd_ = std::chrono::high_resolution_clock::now();

	theDuration_ = theEnd_ - theStart_;

	if (theInfo_ == Global_TimerInfo_ms)
	{
		global_time_duration = theDuration_.count()*1000.0f;
	}
	else if (theInfo_ == Global_TimerInfo_hour)
	{
		global_time_duration = theDuration_.count() / 3600.0f;
	}
	else
	{
		global_time_duration = theDuration_.count();
	}
}

tnbLib::Global_Timer::Global_Timer()
	: theInfo_(Global_TimerInfo_ms)
{
	theStart_ = std::chrono::high_resolution_clock::now();
}

tnbLib::Global_Timer::~Global_Timer()
{
	EstimateDuration();
}