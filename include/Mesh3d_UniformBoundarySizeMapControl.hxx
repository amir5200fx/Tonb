#pragma once
#ifndef _Mesh3d_UniformBoundarySizeMapControl_Header
#define _Mesh3d_UniformBoundarySizeMapControl_Header

#include <Mesh3d_BoundarySizeMapControl.hxx>
#include <Mesh3d_ReferenceValuesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/18/2022 Amir]
	class BoundarySizeMap3d_UniformFaceTool;

	class Mesh3d_UniformBoundarySizeMapControl
		: public Mesh3d_BoundarySizeMapControl
	{

		/*Private Data*/



		// private functions and operators [7/18/2022 Amir]


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Mesh3d_BoundarySizeMapControl>(*this);
		}

	protected:

		// default constructor [7/17/2022 Amir]

		Mesh3d_UniformBoundarySizeMapControl()
		{}

	public:


		// constructors [7/17/2022 Amir]

		Mesh3d_UniformBoundarySizeMapControl
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity3d_Box>& theDomain
		)
			: Mesh3d_BoundarySizeMapControl(theRef, theDomain)
		{}


		// public functions and operators [7/17/2022 Amir]

		TnbMesh_EXPORT std::shared_ptr<BoundarySizeMap3d_UniformFaceTool> 
			SelectMap(const word& theName) const;

		TnbMesh_EXPORT void CreateSizeMap(const word& theName, const std::shared_ptr<Cad_TModel>& theGeometry);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_UniformBoundarySizeMapControl);

#endif // !_Mesh3d_UniformBoundarySizeMapControl_Header
