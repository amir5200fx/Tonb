#pragma once
#ifndef _Aft2d_BndNode_Header
#define _Aft2d_BndNode_Header

#include <Aft2d_Node.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_BndNode
			: public Aft2d_Node
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft2d_Node>(*this);
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_BndNode()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_BndNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Aft2d_Node(theIndex, theCoord)
			{}

			Aft2d_BndNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Aft2d_Node(theIndex, std::move(theCoord))
			{}

		public:

			// Public functions and operators [2/1/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsBoundary() const override;

			virtual TnbLegMesh_EXPORT Standard_Boolean IsCorner() const;
			virtual TnbLegMesh_EXPORT Standard_Boolean IsSegment() const;
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft2d_BndNode);

#endif // !_Aft2d_BndNode_Header
