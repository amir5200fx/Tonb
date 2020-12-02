#pragma once
#ifndef _ShapePx_Profile_Header
#define _ShapePx_Profile_Header

#include <ShapePx_Entity.hxx>
#include <Global_Bound.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class ShapePx_Profile
		: public ShapePx_Entity
	{

		/*Private Data*/


	protected:

		
		template<class... _Types>
		ShapePx_Profile(_Types&... _Args)
			: ShapePx_Entity(_Args...)
		{}

		

	public:


		struct offsetPoint
		{
			offsetPoint()
				: x(0), y(0)
			{}

			offsetPoint(const Standard_Real _x, const Standard_Real _y)
				: x(_x), y(_y)
			{}

			Standard_Real x;
			Standard_Real y;
		};


		virtual Standard_Real Lower() const = 0;

		virtual Standard_Real Upper() const = 0;

		virtual Standard_Real LowerValue() const = 0;

		virtual Standard_Real UpperValue() const = 0;

		virtual std::vector<offsetPoint> RetrieveOffsets() const = 0;

	};
}

#endif // !_ShapePx_Profile_Header
