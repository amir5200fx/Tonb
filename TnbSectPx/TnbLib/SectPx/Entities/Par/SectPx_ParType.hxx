#pragma once
#ifndef _SectPx_ParType_Header
#define _SectPx_ParType_Header

namespace tnbLib
{

	enum class SectPx_ParType
	{
		constant,
		fixed,
		free
	};

	namespace sectPxLib
	{
		typedef SectPx_ParType parType;
	}
}

#endif // !_SectPx_ParType_Header
