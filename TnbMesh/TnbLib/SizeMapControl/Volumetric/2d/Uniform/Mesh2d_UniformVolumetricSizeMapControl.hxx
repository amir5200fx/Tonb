#pragma once
#ifndef _Mesh2d_UniformVolumetricSizeMapControl_Header
#define _Mesh2d_UniformVolumetricSizeMapControl_Header

#include <Mesh2d_VolumetricSizeMapControl.hxx>
#include <Mesh2d_ReferenceValuesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/14/2023 Payvand]
	class Mesh2d_VolumeSizeMapTool;
	class Mesh2d_VolumeSizeMapTool_Info;

	class Mesh2d_UniformVolumetricSizeMapControl
		: public Mesh2d_VolumetricSizeMapControl
	{

		/*Private Data*/


		// Private functions and operators [7/14/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Mesh2d_VolumetricSizeMapControl>(*this);
		}


	protected:

		// default constructor [7/14/2023 Payvand]

		Mesh2d_UniformVolumetricSizeMapControl()
		{}

	public:

		// constructors [7/14/2023 Payvand]

		Mesh2d_UniformVolumetricSizeMapControl
		(
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef, 
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Geo2d_SegmentCloud>& theCloud
		)
			: Mesh2d_VolumetricSizeMapControl(theRef, theDomain, theCloud)
		{}


		// Public functions and operators [7/14/2023 Payvand]

		TnbMesh_EXPORT std::shared_ptr<Mesh2d_VolumeSizeMapTool> 
			SelectMap(const word& theName) const;

		TnbMesh_EXPORT void CreateSizeMap
		(
			const word& theName, 
			const std::shared_ptr<Cad2d_Plane>& theGeometry,
			const std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info>& theInfo
		);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_UniformVolumetricSizeMapControl);

#endif // !_Mesh2d_UniformVolumetricSizeMapControl_Header
