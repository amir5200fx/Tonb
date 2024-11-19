#pragma once
#ifndef _Discret_CurveInfo_Header
#define _Discret_CurveInfo_Header

#include <Discret_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Discret_CurveInfo
	{

		/*Private Data*/

		Standard_Integer theMinSub_;
		Standard_Integer theMaxSub_;


		// Private functions and operators [11/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theMinSub_;
			ar & theMaxSub_;
		}

	public:


		static TnbDiscret_EXPORT Standard_Integer DEFAULT_MIN_NB_SUBDIVIDE;
		static TnbDiscret_EXPORT Standard_Integer DEFAULT_MAX_NB_SUBDIVIDE;

		// default constructor [11/7/2022 Amir]

		Discret_CurveInfo()
			: theMinSub_(DEFAULT_MIN_NB_SUBDIVIDE)
			, theMaxSub_(DEFAULT_MAX_NB_SUBDIVIDE)
		{}


		// constructors [11/7/2022 Amir]


		// public functions and operators [11/7/2022 Amir]

		auto MinSubdivide() const
		{
			return theMinSub_;
		}

		auto MaxSubdivide() const
		{
			return theMaxSub_;
		}

		void SetMinSubdivide(const Standard_Integer n)
		{
			theMinSub_ = n;
		}

		void SetMaxSubdivide(const Standard_Integer n)
		{
			theMaxSub_ = n;
		}
	};
}

#endif // !_Discret_CurveInfo_Header
