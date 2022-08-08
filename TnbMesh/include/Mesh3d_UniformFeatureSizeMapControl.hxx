#pragma once
#ifndef _Mesh3d_UniformFeatureSizeMapControl_Header
#define _Mesh3d_UniformFeatureSizeMapControl_Header

#include <Mesh3d_FeatureSizeMapControl.hxx>
#include <Mesh3d_ReferenceValuesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/18/2022 Amir]
	class BoundarySizeMap3d_UniformSegmentTool;

	class Mesh3d_UniformFeatureSizeMapControl
		: public Mesh3d_FeatureSizeMapControl
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Mesh3d_FeatureSizeMapControl>(*this);
		}

	protected:

		// default constructor [7/18/2022 Amir]

		Mesh3d_UniformFeatureSizeMapControl()
		{}

	public:

		// constructors [7/18/2022 Amir]

		Mesh3d_UniformFeatureSizeMapControl
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity3d_Box>& theDomain
		)
			: Mesh3d_FeatureSizeMapControl(theRef, theDomain)
		{}


		// public functions and operators [7/18/2022 Amir]

		TnbMesh_EXPORT std::shared_ptr<BoundarySizeMap3d_UniformSegmentTool> 
			SelectMap(const word& theName) const;

		TnbMesh_EXPORT void CreateSizeMap(const word& theName, const std::shared_ptr<Cad_TModel>& theGeometry);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_UniformFeatureSizeMapControl);

#endif // !_Mesh3d_UniformFeatureSizeMapControl_Header
