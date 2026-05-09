#pragma once
#ifndef _SectPx_PoleControllerType_Header
#define _SectPx_PoleControllerType_Header

namespace tnbLib
{

	enum class SectPx_PoleControllerType
	{
		weight,
		tightness
	};

	namespace sectPxLib
	{
		typedef SectPx_PoleControllerType poleControllerType;
	}
}

#endif // !_SectPx_PoleControllerType_Header
