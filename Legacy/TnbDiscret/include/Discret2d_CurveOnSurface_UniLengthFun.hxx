#pragma once
#ifndef _Discret2d_CurveOnSurface_UniLengthFun_Header
#define _Discret2d_CurveOnSurface_UniLengthFun_Header

#include <Discret_Module.hxx>
#include <Discret2d_CurveOnSurface_LengthFun.hxx>

namespace tnbLib
{

	class Discret2d_CurveOnSurface_UniLengthFun
		: public Discret2d_CurveOnSurface_LengthFun
	{

		/*Private Data*/

		Standard_Real theSize_;

	public:

		// default constructor [12/1/2022 Payvand]

		Discret2d_CurveOnSurface_UniLengthFun()
			: theSize_(0)
		{}


		// constructors [12/1/2022 Payvand]


		// public functions and operators [12/1/2022 Payvand]

		auto Size() const
		{
			return theSize_;
		}

		TnbDiscret_EXPORT Standard_Boolean
			Subdivide
			(
				const std::shared_ptr<Cad_ParaCurve>& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1
			) const override;

		void SetSize(const Standard_Real theSize)
		{
			theSize_ = theSize;
		}
	};
}

#endif // !_Discret2d_CurveOnSurface_UniLengthFun_Header
