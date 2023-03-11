#pragma once
#ifndef _Aft3d_BoundaryEdge_Header
#define _Aft3d_BoundaryEdge_Header

#include <Aft3d_Edge.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_BoundaryEdge
			: public Aft3d_Edge
		{

			/*Private Data*/


			// Private functions and operators [2/28/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_Edge>(*this);
			}

		protected:

			// default constructor [2/28/2023 Payvand]

			Aft3d_BoundaryEdge()
			{}

			// constructors [2/28/2023 Payvand]

			Aft3d_BoundaryEdge
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Edge(theIndex, theNodes)
			{}

			Aft3d_BoundaryEdge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Edge(theIndex, std::move(theNodes))
			{}

		public:

			// Public functions and operators [2/28/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsBoundary() const override;

			TnbLegMesh_EXPORT virtual Standard_Boolean IsSegment() const;
			TnbLegMesh_EXPORT virtual Standard_Boolean IsFace() const;

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft3d_BoundaryEdge);

#endif // !_Aft3d_BoundaryEdge_Header
