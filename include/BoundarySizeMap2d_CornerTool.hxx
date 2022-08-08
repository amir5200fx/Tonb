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

		Standard_Integer theUnbalancing_;
		Standard_Integer theMinSubdivision_;
		Standard_Integer theMaxSubdivision_;


		//- default constructor

		BoundarySizeMap2d_CornerTool()
		{}


		//- private functions and operators

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh2d_BoundarySizeMapTool>(*this);
			ar & theUnbalancing_;
			ar & theMinSubdivision_;
			ar & theMaxSubdivision_;
		}

	public:

		static TnbMesh_EXPORT unsigned short verbose;

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_UNBALANCING;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MIN_SUBDIVISION;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_SUBDIVISION;


		//- constructors

		TnbMesh_EXPORT BoundarySizeMap2d_CornerTool
		(
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity2d_Box>& theDomain,
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

		auto Unbalancing() const
		{
			return theUnbalancing_;
		}

		TnbMesh_EXPORT void SetUnbalancing(const Standard_Integer theSize);
		TnbMesh_EXPORT void SetMinSubdivision(const Standard_Integer nbLevels);
		TnbMesh_EXPORT void SetMaxSubdivision(const Standard_Integer nbLevels);

		TnbMesh_EXPORT void Perform();

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::BoundarySizeMap2d_CornerTool);

#endif // !_BoundarySizeMap2d_CornerTool_Header
