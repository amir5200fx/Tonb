#pragma once
#ifndef _Aft_MetricPrcsrAnIso_Info_Header
#define _Aft_MetricPrcsrAnIso_Info_Header

#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Global_AccessMethod.hxx>
#include <Mesh_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations

	class Aft_MetricPrcsrAnIso_Info
		: public Geo_MetricPrcsrAnIso_Info
	{

		/*private Data*/

		Standard_Integer theNbIters_;

		Standard_Real theTolerance_;


		// Private functions and operators [12/2/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Geo_MetricPrcsrAnIso_Info>(*this);

			ar & theNbIters_;
			ar & theTolerance_;
		}

	public:

		static TnbMesh_EXPORT const std::string extension;

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_NB_ITERS;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;


		// default constructor [12/2/2021 Amir]

		Aft_MetricPrcsrAnIso_Info()
			: theNbIters_(DEFAULT_NB_ITERS)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		// constructors [12/2/2021 Amir]

		Aft_MetricPrcsrAnIso_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
			: Geo_MetricPrcsrAnIso_Info(theInfo)
		{}

		Aft_MetricPrcsrAnIso_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo,
			const Standard_Integer theNbSamples,
			const Standard_Integer theNbIters,
			const Standard_Real theTolerance
		)
			: Geo_MetricPrcsrAnIso_Info(theInfo, theNbSamples)
			, theNbIters_(theNbIters)
			, theTolerance_(theTolerance)
		{}

		Aft_MetricPrcsrAnIso_Info
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo,
			const Standard_Integer theNbSamples,
			const Standard_Integer theNbIters,
			const Standard_Real theTolerance
		)
			: Geo_MetricPrcsrAnIso_Info(std::move(theInfo), theNbSamples)
			, theNbIters_(theNbIters)
			, theTolerance_(theTolerance)
		{}

		// public functions and operators [12/2/2021 Amir]


		//- macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbIters)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft_MetricPrcsrAnIso_Info);

#endif // !_Aft_MetricPrcsrAnIso_Info_Header