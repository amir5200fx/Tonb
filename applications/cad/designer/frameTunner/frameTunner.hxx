#pragma once
#ifndef _frameTunner_Header
#define _frameTunner_Header

#include "frameTunnerFwd.hxx"
#include "frameTunner_Module.hxx"

#include <memory>

namespace tnbLib
{

	//- Forward Declarations

	namespace appl
	{

		TnbFrameTunner_EXPORT std::tuple<std::pair<int, int>, int> createSlider(const tunner_t& t, int seg, const par_t& p);
		TnbFrameTunner_EXPORT int createSymmTightness(const tunner_t& t, int pole, const par_t& p);

		TnbFrameTunner_EXPORT void importFrame(const tunner_t& t, const frame_t& f);
	}

}

#endif // !_frameTunner_Header