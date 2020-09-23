#pragma once
#ifndef _SectPx_PntType_Header
#define _SectPx_PntType_Header

namespace tnbLib
{

	enum class SectPx_PntType
	{
		fieldFun,
		component,
		empty
	};

	namespace sectPxLib
	{
		typedef SectPx_PntType pntType;
	}
}

#endif // !_SectPx_PntType_Header
