#pragma once
#ifndef _Geo_ProfileFun_Linear_Header
#define _Geo_ProfileFun_Linear_Header

#include <Geo_ProfileFun.hxx>

namespace tnbLib
{

	namespace GeoLib
	{

		class ProfileFun_Linear
			: public Geo_ProfileFun
		{

			/*Private Data*/

			Standard_Real theValue0_;
			Standard_Real theValue1_;

		public:

			ProfileFun_Linear
			(
				const Standard_Real v0,
				const Standard_Real v1,
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: theValue0_(v0), theValue1_(v1)
				, Geo_ProfileFun(theLower, theUpper)
			{}

			ProfileFun_Linear
			(
				const Standard_Integer theIndex,
				const Standard_Real v0,
				const Standard_Real v1,
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: theValue0_(v0), theValue1_(v1)
				, Geo_ProfileFun
				(
					theIndex, theLower,
					theUpper
				)
			{}

			ProfileFun_Linear
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Standard_Real v0,
				const Standard_Real v1,
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: theValue0_(v0), theValue1_(v1)
				, Geo_ProfileFun
				(
					theIndex, theName,
					theLower, theUpper
				)
			{}

			auto Value0() const
			{
				return theValue0_;
			}

			auto Value1() const
			{
				return theValue1_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};
	}
}

#endif // !_Geo_ProfileFun_Linear_Header
