#pragma once
#ifndef _SectPx_RegObjType_Header
#define _SectPx_RegObjType_Header

#include <word.hxx>

#include <SectPx_Module.hxx>

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
		topoSegment,
		extrProfile,
		curveQ,
		limits,
		other
	};

	TnbSectPx_EXPORT word getRegObjTypeName(const SectPx_RegObjType t);

	namespace sectPxLib
	{
		typedef SectPx_RegObjType regObjType;
	}
}

#endif // !_SectPx_RegObjType_Header
