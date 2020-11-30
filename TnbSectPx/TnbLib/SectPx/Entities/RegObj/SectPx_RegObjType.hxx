#pragma once
#ifndef _SectPx_RegObjType_Header
#define _SectPx_RegObjType_Header

#include <word.hxx>

namespace tnbLib
{

	enum class SectPx_RegObjType
	{
		edge,
		segment,
		pole,
		Interface,
		parameter,
		pnt,
		datum,
		fieldFun,
		geoMap,
		cptsMap,
		controller,
		node,
		profile,
		cmptProfile,
		frame,
		overrider,
		offsetProfile,
		cloud,
		shape,
		other
	};

	word getRegObjTypeName(const SectPx_RegObjType t);

	namespace sectPxLib
	{
		typedef SectPx_RegObjType regObjType;
	}
}

#endif // !_SectPx_RegObjType_Header
