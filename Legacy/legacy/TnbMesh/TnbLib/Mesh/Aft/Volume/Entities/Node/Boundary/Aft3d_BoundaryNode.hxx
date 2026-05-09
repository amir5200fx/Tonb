#pragma once
#ifndef _Aft3d_BoundaryNode_Header
#define _Aft3d_BoundaryNode_Header

#include <Aft3d_Node.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_BoundaryNode
			: public Aft3d_Node
		{

			/*Private Data*/


			// Private functions and operators [2/28/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_Node>(*this);
			}

		protected:

			// default constructor [2/27/2023 Payvand]

			Aft3d_BoundaryNode()
			{}


			// constructors [2/27/2023 Payvand]

			explicit Aft3d_BoundaryNode(const Standard_Integer theIndex)
				: Aft3d_Node(theIndex)
			{}


			Aft3d_BoundaryNode
			(
				const Standard_Integer theIndex,
				const Pnt3d& theCoord
			)
				: Aft3d_Node(theIndex, theCoord)
			{}


			Aft3d_BoundaryNode
			(
				const Standard_Integer theIndex,
				Pnt3d&& theCoord
			)
				: Aft3d_Node(theIndex, std::move(theCoord))
			{}


		public:

			// Public functions and operators [2/27/2023 Payvand]

			TnbLegMesh_EXPORT virtual Standard_Boolean IsCorner() const;
			TnbLegMesh_EXPORT virtual Standard_Boolean IsSegment() const;
			TnbLegMesh_EXPORT virtual Standard_Boolean IsFace() const;

			TnbLegMesh_EXPORT Standard_Boolean IsBoundary() const override;

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft3d_BoundaryNode);

#endif // !_Aft3d_BoundaryNode_Header
