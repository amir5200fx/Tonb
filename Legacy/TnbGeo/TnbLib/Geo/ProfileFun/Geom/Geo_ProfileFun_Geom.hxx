#pragma once
#ifndef _Geo_ProfileFun_Geom_Header
#define _Geo_ProfileFun_Geom_Header

#include <Geo_ProfileFun.hxx>
#include <Global_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	namespace geoLib
	{

		class ProfileFun_Geom
			: public Geo_ProfileFun
		{

			/*Private Data*/

			Handle(Geom2d_Curve) theCurve_;


			TNB_SERIALIZATION(TnbGeo_EXPORT);

		public:

			TnbGeo_EXPORT ProfileFun_Geom
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theLower,
				const Standard_Real theUpper
			);

			TnbGeo_EXPORT ProfileFun_Geom
			(
				Handle(Geom2d_Curve)&& theCurve, 
				const Standard_Real theLower, 
				const Standard_Real theUpper
			);

			TnbGeo_EXPORT ProfileFun_Geom
			(
				const Standard_Integer theIndex, 
				const Handle(Geom2d_Curve)& theCurve, 
				const Standard_Real theLower, 
				const Standard_Real theUpper
			);

			TnbGeo_EXPORT ProfileFun_Geom
			(
				const Standard_Integer theIndex,
				Handle(Geom2d_Curve)&& theCurve,
				const Standard_Real theLower, 
				const Standard_Real theUpper
			);

			TnbGeo_EXPORT ProfileFun_Geom
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const Handle(Geom2d_Curve)& theCurve, 
				const Standard_Real theLower, 
				const Standard_Real theUpper
			);

			TnbGeo_EXPORT ProfileFun_Geom
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				Handle(Geom2d_Curve)&& theCurve, 
				const Standard_Real theLower,
				const Standard_Real theUpper
			);


			const auto& Curve() const
			{
				return theCurve_;
			}

			TnbGeo_EXPORT Standard_Real Value(const Standard_Real x) const override;


		};
	}
}

#endif // !_Geo_ProfileFun_Geom_Header
