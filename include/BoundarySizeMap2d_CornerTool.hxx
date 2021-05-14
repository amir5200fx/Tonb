#pragma once
#ifndef _BoundarySizeMap2d_CornerTool_Header
#define _BoundarySizeMap2d_CornerTool_Header

#include <Mesh2d_BoundarySizeMapTool.hxx>

namespace tnbLib
{

	class BoundarySizeMap2d_CornerTool
		: public Mesh2d_BoundarySizeMapTool
	{

		/*Private Data*/

		Standard_Integer theBucketSize_;
		Standard_Integer theMinSubdivision_;
		Standard_Integer theMaxSubdivision_;


		//- default constructor

		BoundarySizeMap2d_CornerTool()
		{}


	public:


		static TnbMesh_EXPORT const Standard_Integer DEFAULT_BUCKETSIZE;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MIN_SUBDIVISION;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_SUBDIVISION;


		//- constructors

		TnbMesh_EXPORT BoundarySizeMap2d_CornerTool
		(
			const std::shared_ptr<Mesh_ReferenceValues>& theRef,
			const std::shared_ptr<Cad2d_Plane>& thePlane
		);


		//- public functions and operators

		auto MaxSubdivision() const
		{
			return theMaxSubdivision_;
		}

		auto MinSubdivision() const
		{
			return theMinSubdivision_;
		}

		TnbMesh_EXPORT void SetBucketSize(const Standard_Integer theSize);
		TnbMesh_EXPORT void SetMinSubdivision(const Standard_Integer nbLevels);
		TnbMesh_EXPORT void SetMaxSubdivision(const Standard_Integer nbLevels);

		TnbMesh_EXPORT void Perform();

	};
}

#endif // !_BoundarySizeMap2d_CornerTool_Header
