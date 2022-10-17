#pragma once
#ifndef _Geo3d_ApprxSurfPatch_Info_Header
#define _Geo3d_ApprxSurfPatch_Info_Header

#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Geo3d_ApprxSurfPatch_Info
	{

		/*Private Data*/

		Standard_Integer theMinSubdivide_;
		Standard_Integer theMaxSubdivide_;

		Standard_Integer theMaxUnbalancing_;

		Standard_Real theTolerance_;

		Standard_Boolean doBalance_;


		// private functions and operators [9/5/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theMinSubdivide_;
			ar & theMaxSubdivide_;

			ar & theMaxUnbalancing_;

			ar & theTolerance_;
			ar & doBalance_;
		}

	public:

		static Standard_Integer DEFAULT_MIN_SUBDIVIDE;
		static Standard_Integer DEFAULT_MAX_SUBDIVIDE;

		static Standard_Integer DEFAULT_MAX_UNBALANCING;

		static Standard_Real DEFAULT_TOLERANCE;

		// default constructor [9/5/2022 Amir]

		Geo3d_ApprxSurfPatch_Info()
			: theMinSubdivide_(DEFAULT_MIN_SUBDIVIDE)
			, theMaxSubdivide_(DEFAULT_MAX_SUBDIVIDE)
			, theMaxUnbalancing_(DEFAULT_MAX_UNBALANCING)
			, theTolerance_(DEFAULT_TOLERANCE)
			, doBalance_(Standard_True)
		{}

		// constructors [9/5/2022 Amir]


		// public functions and operators [9/5/2022 Amir]

		auto MinSubdivide() const
		{
			return theMinSubdivide_;
		}

		auto MaxSubdivie() const
		{
			return theMaxSubdivide_;
		}

		auto MaxUnbalancing() const
		{
			return theMaxUnbalancing_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto DoBalance() const
		{
			return doBalance_;
		}

		void SetMinSubdivide(const Standard_Integer n)
		{
			theMinSubdivide_ = n;
		}

		void SetMaxSubdivide(const Standard_Integer n)
		{
			theMaxSubdivide_ = n;
		}

		void SetMaxUnbalancing(const Standard_Integer n)
		{
			theMaxUnbalancing_ = n;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void DoBalance(const Standard_Boolean cond)
		{
			doBalance_ = cond;
		}
	};
}

#endif // !_Geo3d_ApprxSurfPatch_Info_Header
