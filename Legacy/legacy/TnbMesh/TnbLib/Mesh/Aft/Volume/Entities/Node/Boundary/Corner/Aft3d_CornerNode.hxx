#pragma once
#ifndef _Aft3d_CornerNode_Header
#define _Aft3d_CornerNode_Header

#include <Aft3d_BoundaryNode.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_CornerNode
			: public Aft3d_BoundaryNode
		{

			/*Private Data*/


			// Private functions and operators [2/28/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_BoundaryNode>(*this);
			}

		public:

			// default constructor [2/27/2023 Payvand]

			Aft3d_CornerNode()
			{}

			// constructors [2/27/2023 Payvand]

			explicit Aft3d_CornerNode(const Standard_Integer theIndex)
				: Aft3d_BoundaryNode(theIndex)
			{}

			Aft3d_CornerNode
			(
				const Standard_Integer theIndex,
				const Pnt3d& theCoord
			)
				: Aft3d_BoundaryNode(theIndex, theCoord)
			{}

			Aft3d_CornerNode
			(
				const Standard_Integer theIndex,
				Pnt3d&& theCoord
			)
				: Aft3d_BoundaryNode(theIndex, std::move(theCoord))
			{}

			// Public functions and operators [2/27/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsCorner() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_CornerNode);

#endif // !_Aft3d_CornerNode_Header
