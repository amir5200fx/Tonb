#pragma once
#ifndef _Aft_MetricPrcsr_Info_Header
#define _Aft_MetricPrcsr_Info_Header

#include <Geo_MetricPrcsr_Info.hxx>

namespace tnbLib
{

	class Aft_MetricPrcsr_Info
		: public Geo_MetricPrcsr_Info
	{

		/*Private Data*/


		// Private functions and operators [12/4/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo_MetricPrcsr_Info>(*this);
		}

	public:

		static TnbMesh_EXPORT const std::string extension;

		// default constructor [12/4/2021 Amir]

		Aft_MetricPrcsr_Info()
		{}


		// constructors [12/4/2021 Amir]

		Aft_MetricPrcsr_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
			: Geo_MetricPrcsr_Info(theInfo)
		{}

		Aft_MetricPrcsr_Info
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo
		)
			: Geo_MetricPrcsr_Info(std::move(theInfo))
		{}

		// Public functions and operators [12/4/2021 Amir]

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft_MetricPrcsr_Info);

#endif // !_Aft_MetricPrcsr_Info_Header
