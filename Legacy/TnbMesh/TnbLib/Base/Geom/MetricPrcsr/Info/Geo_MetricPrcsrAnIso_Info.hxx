#pragma once
#ifndef _Geo_MetricPrcsrAnIso_Info_Header
#define _Geo_MetricPrcsrAnIso_Info_Header

#include <Mesh_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Global_Handle.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;

	class Geo_MetricPrcsrAnIso_Info
	{

		/*Private Data*/

		Standard_Integer theNbSamples_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntgInfo_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_NB_SAMPLES;


		// default constructor [12/4/2021 Amir]

		Geo_MetricPrcsrAnIso_Info()
			: theNbSamples_(DEFAULT_NB_SAMPLES)
		{}


		// constructors [12/4/2021 Amir]

		Geo_MetricPrcsrAnIso_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
			: theNbSamples_(DEFAULT_NB_SAMPLES)
			, theIntgInfo_(theInfo)
		{}

		Geo_MetricPrcsrAnIso_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo,
			const Standard_Integer theNbSamples
		)
			: theNbSamples_(theNbSamples)
			, theIntgInfo_(theInfo)
		{}

		Geo_MetricPrcsrAnIso_Info
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo
		)
			: theIntgInfo_(std::move(theInfo))
		{}

		Geo_MetricPrcsrAnIso_Info
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo,
			const Standard_Integer theNbSamples
		)
			: theIntgInfo_(std::move(theInfo))
			, theNbSamples_(theNbSamples)
		{}


		virtual ~Geo_MetricPrcsrAnIso_Info()
		{}

		// public functions and operators [12/4/2021 Amir]

		const auto& IntegInfo() const
		{
			return theIntgInfo_;
		}

		void OverrideIntegInfo
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
		{
			theIntgInfo_ = theInfo;
		}

		void OverrideIntegInfo
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo
		)
		{
			theIntgInfo_ = std::move(theInfo);
		}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbSamples)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_MetricPrcsrAnIso_Info);

#endif // !_Geo_MetricPrcsrAnIso_Info_Header