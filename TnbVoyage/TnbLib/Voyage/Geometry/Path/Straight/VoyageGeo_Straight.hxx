#pragma once
#ifndef _VoyageGeo_Straight_Header
#define _VoyageGeo_Straight_Header

#include <VoyageGeo_Path.hxx>

namespace tnbLib
{

	class VoyageGeo_Straight
		: public VoyageGeo_Path
	{

		/*Private Data*/

		Pnt2d theP0_;
		Pnt2d theP1_;

	public:

		// default constructor [7/10/2023 Payvand]


		// constructors [7/10/2023 Payvand]

		VoyageGeo_Straight(const Pnt2d& theP0, const Pnt2d& theP1)
			: theP0_(theP0)
			, theP1_(theP1)
		{}


		// Public functions and operators [7/10/2023 Payvand]

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}

		Pnt2d Value(const Standard_Real) const override;
		Dir2d CalcNormal(const Standard_Real) const override;

		Pnt2d Start() const override;
		Pnt2d End() const override;

	};

}

#endif // !_VoyageGeo_Straight_Header
