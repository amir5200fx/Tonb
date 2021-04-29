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


		static const Standard_Integer DEFAULT_BUCKETSIZE;

		BoundarySizeMap2d_CornerTool(const std::shared_ptr<Mesh_ReferenceValues>& theRef, const std::shared_ptr<Cad2d_Plane>& thePlane);


		auto MaxSubdivision() const
		{
			return theMaxSubdivision_;
		}

		auto MinSubdivision() const
		{
			return theMinSubdivision_;
		}

		void SetBucketSize(const Standard_Integer theSize);

		void Perform();

	};
}

#endif // !_BoundarySizeMap2d_CornerTool_Header
