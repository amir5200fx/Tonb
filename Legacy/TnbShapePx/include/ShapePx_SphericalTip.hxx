#pragma once
#ifndef _ShapePx_SphericalTip_Header
#define _ShapePx_SphericalTip_Header

#include <ShapePx_Tip.hxx>

namespace tnbLib
{

	class ShapePx_SphericalTip
		: public ShapePx_Tip
	{

		/*Private Data*/

	public:

		ShapePx_SphericalTip()
		{}

		ShapePx_SphericalTip(const Standard_Integer theIndex, const word& theName);

		Standard_Boolean IsSpherical() const override;
	};
}

#endif // !_ShapePx_SphericalTip_Header
