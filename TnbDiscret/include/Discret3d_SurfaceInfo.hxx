#pragma once
#ifndef _Discret3d_SurfaceInfo_Header
#define _Discret3d_SurfaceInfo_Header

#include <Discret_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [11/7/2022 Amir]

	class Discret_CurveInfo;

	class Discret3d_SurfaceInfo
	{

		/*private Data*/

		Standard_Integer theMinSubs_;
		Standard_Integer theMaxSubs_;

		Standard_Real theTolerance_;

		Standard_Boolean ApplyPostBalance_;

		// Private functions and operators [11/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theMinSubs_;
			ar & theMaxSubs_;

			ar & theTolerance_;

			ar & ApplyPostBalance_;
		}

	public:

		static TnbDiscret_EXPORT Standard_Integer DEFAULT_MIN_NB_SUBS;
		static TnbDiscret_EXPORT Standard_Integer DEFAULT_MAX_NB_SUBS;

		static TnbDiscret_EXPORT Standard_Real DEFAULT_TOLERANCE;

		// default constructor [11/7/2022 Amir]

		Discret3d_SurfaceInfo()
			: theMinSubs_(DEFAULT_MIN_NB_SUBS)
			, theMaxSubs_(DEFAULT_MAX_NB_SUBS)
			, theTolerance_(DEFAULT_TOLERANCE)
			, ApplyPostBalance_(Standard_True)
		{}


		// constructors [11/7/2022 Amir]


		// public functions and operators [11/7/2022 Amir]

		auto MinNbSubs() const
		{
			return theMinSubs_;
		}

		auto MaxNbSubs() const
		{
			return theMaxSubs_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto PostBalance() const
		{
			return ApplyPostBalance_;
		}

		void SetMinNbSubs(const Standard_Integer n)
		{
			theMinSubs_ = n;
		}

		void SetMaxNbSubs(const Standard_Integer n)
		{
			theMaxSubs_ = n;
		}

		void SetTolerance(const Standard_Real theTolerance)
		{
			theTolerance_ = theTolerance;
		}

		void ApplyPostBalance(const Standard_Boolean apply)
		{
			ApplyPostBalance_ = apply;
		}
	};
}

#endif // !_Discret3d_SurfaceInfo_Header
