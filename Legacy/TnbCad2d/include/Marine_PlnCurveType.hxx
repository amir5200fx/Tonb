#pragma once
#ifndef _Marine_PlnCurveType_Header
#define _Marine_PlnCurveType_Header

namespace tnbLib
{
	enum class Marine_PlnCurveType
	{
		displacer,
		sail,
		tank,
		water,
		waterLine,
		wetted,
		dry
	};

	namespace marineLib
	{
		typedef Marine_PlnCurveType curveType;
	}
}

#endif // !_Marine_PlnCurveType_Header
