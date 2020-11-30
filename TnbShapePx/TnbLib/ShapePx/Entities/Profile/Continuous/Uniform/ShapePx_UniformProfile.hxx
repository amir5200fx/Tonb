#pragma once
#ifndef _ShapePx_UniformProfile_Header
#define _ShapePx_UniformProfile_Header

#include <ShapePx_Profile.hxx>

namespace tnbLib
{

	class ShapePx_UniformProfile
		: public ShapePx_Profile
	{

		/*Private Data*/

		Standard_Real theValue_;

	public:

		ShapePx_UniformProfile();

		ShapePx_UniformProfile(const Standard_Real x);

		ShapePx_UniformProfile(const Standard_Integer theIndex, const Standard_Real x);

		ShapePx_UniformProfile(const Standard_Integer theIndex, const word& theName, const Standard_Real x);

		Standard_Real Value(const Standard_Real x) const override
		{
			return theValue_;
		}

		void SetValue(const Standard_Real x)
		{
			theValue_ = x;
		}
	};
}

#endif // !_ShapePx_UniformProfile_Header
