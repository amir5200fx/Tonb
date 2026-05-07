#pragma once
#ifndef _frameTuner_Header
#define _frameTuner_Header

#include "frameTunerFwd.hxx"
#include "frameTuner_Module.hxx"

#include <memory>

namespace tnbLib
{

	//- Forward Declarations

	namespace appl
	{

		TnbFrameTunner_EXPORT std::tuple<std::pair<int, int>, int> createSlider(const tuner_t& t, int seg, const par_t& p);
		TnbFrameTunner_EXPORT std::tuple<std::pair<int, int>, int> createSlider(const tuner_t& t, int seg, const coord_t& p);
		TnbFrameTunner_EXPORT int createWeight(const tuner_t& t, int pole, const par_t& p);
		TnbFrameTunner_EXPORT int createSymmTightness(const tuner_t& t, int pole, const par_t& p);

		TnbFrameTunner_EXPORT void importFrame(const tuner_t& t, const frame_t& f);
	}

}

#endif // !_frameTuner_Header
