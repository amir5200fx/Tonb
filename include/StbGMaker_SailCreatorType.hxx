#pragma once
#ifndef _StbGMaker_SailCreatorType_Header
#define _StbGMaker_SailCreatorType_Header

namespace tnbLib
{

	enum class StbGMaker_SailCreatorType
	{
		constArea,
		profile,
		plane,
		shape,
		noShape
	};

	namespace stbGmakerLib
	{
		typedef StbGMaker_SailCreatorType sailCreatotType;
	}
}

#endif // !_StbGMaker_SailCreatorType_Header
