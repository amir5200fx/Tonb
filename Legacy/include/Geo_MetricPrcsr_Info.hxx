#pragma once
#ifndef _Geo_MetricPrcsr_Info_Header
#define _Geo_MetricPrcsr_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;

	class Geo_MetricPrcsr_Info
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntgInfo_;

		// Private Data [12/4/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructor [12/4/2021 Amir]

		Geo_MetricPrcsr_Info()
		{}


		// constructors [12/4/2021 Amir]

		Geo_MetricPrcsr_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
			: theIntgInfo_(theInfo)
		{}

		Geo_MetricPrcsr_Info
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo
		)
			: theIntgInfo_(std::move(theInfo))
		{}


		virtual ~Geo_MetricPrcsr_Info()
		{}


		// Public functions and operators [12/4/2021 Amir]

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
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_MetricPrcsr_Info);

#endif // !_Geo_MetricPrcsr_Info_Header
