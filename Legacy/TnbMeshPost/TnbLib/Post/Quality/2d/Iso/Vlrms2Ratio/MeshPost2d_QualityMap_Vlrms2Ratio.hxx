#pragma once
#ifndef _MeshPost2d_QualityMap_Vlrms2Ratio_Header
#define _MeshPost2d_QualityMap_Vlrms2Ratio_Header

#include <MeshPost2d_QualityMap.hxx>

namespace tnbLib
{

	class MeshPost2d_QualityMap_Vlrms2Ratio
		: public MeshPost2d_QualityMap
	{

		/*Private Data*/


		// friend functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<MeshPost_QualityMap>(*this);
		}

	public:

		// default constructor [9/18/2022 Amir]

		MeshPost2d_QualityMap_Vlrms2Ratio()
			= default;


		// constructors [9/18/2022 Amir]

		explicit MeshPost2d_QualityMap_Vlrms2Ratio(const std::shared_ptr<Aft2d_MetricPrcsr>& theMetrics)
			: MeshPost2d_QualityMap(theMetrics)
		{}

		MeshPost2d_QualityMap_Vlrms2Ratio(std::shared_ptr<Aft2d_MetricPrcsr>&& theMetrics)
			: MeshPost2d_QualityMap(std::move(theMetrics))
		{}


		// public functions and operators [9/18/2022 Amir]

		TnbMeshPost_EXPORT Standard_Real
			CalcQuality(const Aft2d_Element&) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MeshPost2d_QualityMap_Vlrms2Ratio);

#endif // !_MeshPost2d_QualityMap_Vlrms2Ratio_Header
