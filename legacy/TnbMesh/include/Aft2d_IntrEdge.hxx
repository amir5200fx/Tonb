#pragma once
#ifndef _Aft2d_IntrEdge_Header
#define _Aft2d_IntrEdge_Header

#include <Aft2d_Edge.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_IntrEdge
			: public Aft2d_Edge
		{

			/*Private Data*/


			// Private functions and operators [5/24/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft2d_Edge>(*this);
			}

		public:

			// default constructor [2/1/2023 Payvand]

			Aft2d_IntrEdge()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_IntrEdge
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Aft2d_Node>, 2>& theNodes
			)
				: Aft2d_Edge(theIndex ,theNodes)
			{}

			Aft2d_IntrEdge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft2d_Node>, 2>&& theNodes
			)
				: Aft2d_Edge(theIndex, std::move(theNodes))
			{}


			// Public functions and operators [2/1/2023 Payvand]


			TnbLegMesh_EXPORT Standard_Boolean IsInterior() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft2d_IntrEdge);

#endif // !_Aft2d_IntrEdge_Header
