#pragma once
#ifndef _ShapePx_LinearProfile_Header
#define _ShapePx_LinearProfile_Header

#include <ShapePx_Profile.hxx>

namespace tnbLib
{

	class ShapePx_LinearProfile
		: public ShapePx_Profile
	{

		/*Private Data*/

		Standard_Real theValue0_;
		Standard_Real theValue1_;

	public:


		Standard_Real Value(const Standard_Real x) const override;
	};
}

#endif // !_ShapePx_LinearProfile_Header
