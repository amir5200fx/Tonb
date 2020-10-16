#pragma once
#ifndef _ShapePx_Profile_Header
#define _ShapePx_Profile_Header

#include <ShapePx_Entity.hxx>
#include <Global_Bound.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class ShapePx_Profile
		: public ShapePx_Entity
		, public Global_Bound<Standard_Real>
	{

		/*Private Data*/

	protected:



	public:

		virtual Standard_Real Value(const Standard_Real x) const = 0;
	};
}

#endif // !_ShapePx_Profile_Header
