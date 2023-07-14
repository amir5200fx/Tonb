#pragma once
#ifndef _Discret2d_PlnCurve_UniLengthFun_Header
#define _Discret2d_PlnCurve_UniLengthFun_Header

#include <Discret2d_PlnCurve_LengthFun.hxx>

namespace tnbLib
{

	class Discret2d_PlnCurve_UniLengthFun
		: public Discret2d_PlnCurve_LengthFun
	{

		/*Private Data*/

		Standard_Real theSize_;

	public:

		// default constructor [11/7/2022 Amir]

		Discret2d_PlnCurve_UniLengthFun()
			: theSize_(0)
		{}


		// constructors [11/7/2022 Amir]


		// public functions and operators [11/7/2022 Amir]


		auto Size() const
		{
			return theSize_;
		}

		TnbDiscret_EXPORT Standard_Boolean
			Subdivide
			(
				const std::shared_ptr<Pln_Curve>& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1
			) const override;

		void SetSize(const Standard_Real theSize)
		{
			theSize_ = theSize;
		}
	};
}

#endif // !_Discret2d_PlnCurve_UniLengthFun_Header
