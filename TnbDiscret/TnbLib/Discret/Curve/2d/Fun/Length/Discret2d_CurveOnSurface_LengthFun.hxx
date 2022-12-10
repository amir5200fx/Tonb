#pragma once
#ifndef _Discret2d_CurveOnSurface_LengthFun_Header
#define _Discret2d_CurveOnSurface_LengthFun_Header

#include <Discret2d_Curve_Function.hxx>

namespace tnbLib
{

	// Forward Declarations [12/1/2022 Payvand]
	class Cad_GeomSurface;

	class Discret2d_CurveOnSurface_LengthFun
		: public Discret2d_Curve_Function
	{

		/*Private Data*/

		std::shared_ptr<Cad_GeomSurface> theSurface_;

	protected:

		// default constructor [12/1/2022 Payvand]

		Discret2d_CurveOnSurface_LengthFun()
		{}


		// constructors [12/1/2022 Payvand]

	public:

		// public functions and operators [12/1/2022 Payvand]

		const auto& Surface() const
		{
			return theSurface_;
		}

		void SetSurface(const std::shared_ptr<Cad_GeomSurface>& theSurface)
		{
			theSurface_ = theSurface;
		}
	};
}

#endif // !_Discret2d_CurveOnSurface_LengthFun_Header
