#pragma once
#ifndef _Aft_SizeCorr_IterativeInfo_Header
#define _Aft_SizeCorr_IterativeInfo_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Aft_SizeCorr_IterativeInfo
	{

		/*Private Data*/

		Standard_Integer theMaxNbIters_;

		Standard_Real theTolerance_;
		Standard_Real theUnderRelaxation_;

		Standard_Boolean IgnoreNonConvergency_;


		// private functions and operators [3/1/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theMaxNbIters_;
			ar & theTolerance_;
			ar & theUnderRelaxation_;
			ar & IgnoreNonConvergency_;
		}

	public:

		static TnbMesh_EXPORT const std::string extension;

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_NB_ITERATIONS;

		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_UNDER_RELAXATION;

		// default constructor [3/1/2022 Amir]

		Aft_SizeCorr_IterativeInfo()
			: theMaxNbIters_(DEFAULT_MAX_NB_ITERATIONS)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theUnderRelaxation_(DEFAULT_UNDER_RELAXATION)
			, IgnoreNonConvergency_(Standard_True)
		{}

		auto IgnoreNonConvergency() const
		{
			return IgnoreNonConvergency_;
		}

		void SetIgnoreNonConvergency(const Standard_Boolean theConv)
		{
			IgnoreNonConvergency_ = theConv;
		}

		//- Macros

		GLOBAL_ACCESS_SINGLE(Standard_Integer, MaxNbIters)
			GLOBAL_ACCESS_SINGLE(Standard_Real, Tolerance)
			GLOBAL_ACCESS_SINGLE(Standard_Real, UnderRelaxation)
	};
}

#endif // !_Aft_SizeCorr_IterativeInfo_Header
