#pragma once
#ifndef _Aft3d_SegmentEdge_Header
#define _Aft3d_SegmentEdge_Header

#include <Aft3d_BoundaryEdge.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_SegmentEdge
			: public Aft3d_BoundaryEdge
		{

			/*Private Data*/


			// Private functions and operators [2/28/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_BoundaryEdge>(*this);
			}

		public:

			// default constructor [2/28/2023 Payvand]

			Aft3d_SegmentEdge()
			{}

			// constructors [2/28/2023 Payvand]

			Aft3d_SegmentEdge
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_BoundaryEdge(theIndex, theNodes)
			{}
			
			Aft3d_SegmentEdge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_BoundaryEdge(theIndex, std::move(theNodes))
			{}

			// Public functions and operators [2/28/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsSegment() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_SegmentEdge);

#endif // !_Aft3d_SegmentEdge_Header
