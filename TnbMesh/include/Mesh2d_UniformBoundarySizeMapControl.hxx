#pragma once
#ifndef _Mesh2d_UniformBoundarySizeMapControl_Header
#define _Mesh2d_UniformBoundarySizeMapControl_Header

#include <Mesh2d_BoundarySizeMapControl.hxx>
#include <Mesh2d_ReferenceValuesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/23/2023 Payvand]
	class BoundarySizeMap2d_UniformSegmentTool;

	class Mesh2d_UniformBoundarySizeMapControl
		: public Mesh2d_BoundarySizeMapControl
	{

		/*Private Data*/


		// private functions and operators [6/23/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Mesh2d_BoundarySizeMapControl>(*this);
		}

	protected:

		// default constructor [6/23/2023 Payvand]

		Mesh2d_UniformBoundarySizeMapControl()
		{}

	public:

		// constructors [6/23/2023 Payvand]

		Mesh2d_UniformBoundarySizeMapControl
		(
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Geo2d_SegmentCloud>& theCloud
		)
			: Mesh2d_BoundarySizeMapControl(theRef, theDomain, theCloud)
		{}


		// Public functions and operators [6/23/2023 Payvand]

		TnbMesh_EXPORT std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool>
			SelectMap(const word& theName) const;

		TnbMesh_EXPORT void CreateSizeMap
		(
			const word& theName,
			const std::shared_ptr<Cad2d_Plane>& theGeometry,
			const std::shared_ptr<Geo2d_SegmentCloud>& theCloud
		);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_UniformBoundarySizeMapControl);

#endif // !_Mesh2d_UniformBoundarySizeMapControl_Header
