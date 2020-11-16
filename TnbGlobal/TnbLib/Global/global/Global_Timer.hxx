#pragma once
#ifndef _Global_Timer_Header
#define _Global_Timer_Header

#include <thread>
#include <chrono>

#include <Global_Module.hxx>

namespace tnbLib
{

	enum Global_TimerInfo
	{
		Global_TimerInfo_ms,
		Global_TimerInfo_s,
		Global_TimerInfo_hour
	};

	extern float global_time_duration;

	class Global_Timer
	{

		std::chrono::time_point<std::chrono::steady_clock> theStart_;
		std::chrono::time_point<std::chrono::steady_clock> theEnd_;

		std::chrono::duration<float> theDuration_;

		Global_TimerInfo theInfo_;

		/*Private Data*/

		TnbGlobal_EXPORT void EstimateDuration();

	public:

		TnbGlobal_EXPORT Global_Timer();

		TnbGlobal_EXPORT ~Global_Timer();

		void SetInfo(const Global_TimerInfo theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#endif // !_Global_Timer_Header
