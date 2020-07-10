#pragma once
#ifndef _Marine_SailModelType_Header
#define _Marine_SailModelType_Header

namespace tnbLib
{

	enum class Marine_SailModelType
	{
		constant_area,
		profile_area,
		shape,
		lateral_plane,
		surface
	};
}

#endif // !_Marine_SailModelType_Header
