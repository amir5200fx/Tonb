#pragma once
#ifndef _Geo_ProfileFun_Const_Header
#define _Geo_ProfileFun_Const_Header

#include <Geo_ProfileFun.hxx>

namespace tnbLib
{

	namespace GeoLib
	{

		class ProfileFun_Const
			: public Geo_ProfileFun
		{

			/*Private Data*/

			Standard_Real theValue_;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<Geo_ProfileFun>(*this);
				ar & theValue_;
			}

		public:

			ProfileFun_Const
			(
				const Standard_Real x,
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: Geo_ProfileFun(theLower, theUpper)
				, theValue_(x)
			{}

			ProfileFun_Const
			(
				const Standard_Integer theIndex, 
				const Standard_Real x,
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: Geo_ProfileFun
				(
					theIndex, theLower,
					theUpper
				)
				, theValue_(x)
			{}

			ProfileFun_Const
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const Standard_Real x,
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: Geo_ProfileFun
				(
					theIndex, theName,
					theLower, theUpper
				)
				, theValue_(x)
			{}


			Standard_Real Value(const Standard_Real x) const override
			{
				return theValue_;
			}


		};
	}
}

#endif // !_Geo_ProfileFun_Const_Header
