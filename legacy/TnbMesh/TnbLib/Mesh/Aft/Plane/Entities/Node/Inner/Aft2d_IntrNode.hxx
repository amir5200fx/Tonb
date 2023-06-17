#pragma once
#ifndef _Aft2d_IntrNode_Header
#define _Aft2d_IntrNode_Header

#include <Aft2d_Node.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_IntrNode
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

		public:

			// default constructor [2/1/2023 Payvand]

			Aft2d_IntrNode()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_IntrNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Aft2d_Node(theIndex, theCoord)
			{}

			Aft2d_IntrNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Aft2d_Node(theIndex, std::move(theCoord))
			{}


			// Public functions and operators [2/1/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsInterior() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft2d_IntrNode);

#endif // !_Aft2d_IntrNode_Header
