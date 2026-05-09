#pragma once
#ifndef _Cad_SingularType_Header
#define _Cad_SingularType_Header

namespace tnbLib
{

	enum class Cad_SingularType
	{
		pole_corner,
		pole_loop,
		pole_partial_side,
		pole_whole_side,
		line_corner,
		line_dangle,
		line_loop,
		line_two_side,
		line_whole_side
	};
}

#endif // !_Cad_SingularType_Header
