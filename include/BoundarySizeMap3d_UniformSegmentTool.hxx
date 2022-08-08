#pragma once
#ifndef _BoundarySizeMap3d_UniformSegmentTool_Header
#define _BoundarySizeMap3d_UniformSegmentTool_Header

#include <BoundarySizeMap3d_SegmentTool.hxx>

namespace tnbLib
{

	class BoundarySizeMap3d_UniformSegmentTool
		: public BoundarySizeMap3d_SegmentTool
	{

		/*Private Data*/


		// private functions and operators [7/20/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<BoundarySizeMap3d_SegmentTool>(*this);
		}

	protected:

		// default constructor [7/18/2022 Amir]

		BoundarySizeMap3d_UniformSegmentTool()
		{}

	public:

		// constructors [7/18/2022 Amir]

		BoundarySizeMap3d_UniformSegmentTool
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef, 
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const std::shared_ptr<Cad_TModel>& theModel
		)
			: BoundarySizeMap3d_SegmentTool(theRef, theDomain, theModel)
		{}

		// public functions and operators [7/18/2022 Amir]

		TnbMesh_EXPORT void Perform() override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::BoundarySizeMap3d_UniformSegmentTool);

#endif // !_BoundarySizeMap3d_UniformSegmentTool_Header
