#pragma once
#ifndef _frameTunerFwd_Header
#define _frameTunerFwd_Header

#include <frameMakerFwd.hxx>

#include <SectPx_PolesFwd.hxx>
#include <SectPx_ParsFwd.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class SectPx_FrameTuner;
	class SectPx_Segment;

	namespace appl
	{

		typedef std::shared_ptr<SectPx_FrameTuner> tuner_t;
		//typedef std::shared_ptr<SectPx_Frame> frame_t;

		typedef std::shared_ptr<SectPx_Pole> pole_t;
		typedef std::shared_ptr<SectPx_Segment> segment_t;
		typedef std::shared_ptr<SectPx_Par> par_t;
	}
}

#endif // !_frameTunerFwd_Header
