#pragma once
#ifndef _Aft3d_InteriorNode_Header
#define _Aft3d_InteriorNode_Header

#include <Aft3d_Node.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_InteriorNode
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

		public:

			// default constructor [2/28/2023 Payvand]

			Aft3d_InteriorNode()
			{}


			// constructors [2/28/2023 Payvand]

			Aft3d_InteriorNode
			(
				const Standard_Integer theIndex,
				const Pnt3d& theCoord
			)
				: Aft3d_Node(theIndex, theCoord)
			{}

			Aft3d_InteriorNode
			(
				const Standard_Integer theIndex,
				Pnt3d&& theCoord
			)
				: Aft3d_Node(theIndex, std::move(theCoord))
			{}

			// Public functions and operators [2/28/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsInterior() const override;

		};

	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_InteriorNode);

#endif // !_Aft3d_InteriorNode_Header
