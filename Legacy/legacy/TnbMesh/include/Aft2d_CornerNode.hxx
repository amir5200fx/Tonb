#pragma once
#ifndef _Aft2d_CornerNode_Header
#define _Aft2d_CornerNode_Header

#include <Aft2d_BndNode.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_CornerNode
			: public Aft2d_BndNode
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft2d_BndNode>(*this);
			}

		public:

			// default constructor [2/1/2023 Payvand]

			Aft2d_CornerNode()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_CornerNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Aft2d_BndNode(theIndex, theCoord)
			{}

			Aft2d_CornerNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Aft2d_BndNode(theIndex, std::move(theCoord))
			{}


			// Public functions and operators [2/1/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsCorner() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft2d_CornerNode);

#endif // !_Aft2d_CornerNode_Header
