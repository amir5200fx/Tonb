#pragma once
#ifndef _Geo_BasicApprxCurveAdaptor_Header
#define _Geo_BasicApprxCurveAdaptor_Header

#include <Geo_BasicApprxCurve_Traits.hxx>
#include <Geo_Traits.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	template<class CurveType>
	class Geo_BasicApprxCurveAdaptor
	{

		/*Private Data*/

		const CurveType& theCurve_;

	public:

		typedef typename remove_pointer<CurveType>::type CurveTypeR;
		typedef typename Geo_BasicApprxCurveAdaptor_Traits<CurveTypeR>::ptType Point;

		// default constructor [8/25/2022 Amir]


		// constructors [8/25/2022 Amir]

		explicit Geo_BasicApprxCurveAdaptor(const CurveType& theCurve)
			: theCurve_(theCurve)
		{}


		// public functions and operators [8/25/2022 Amir]

		const auto& Geometry() const
		{
			return theCurve_;
		}

		Point Value(const Standard_Real) const;
	};
}

#endif // !_Geo_BasicApprxCurveAdaptor_Header
