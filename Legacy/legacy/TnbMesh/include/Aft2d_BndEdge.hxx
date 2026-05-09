#pragma once
#ifndef _Aft2d_BndEdge_Header
#define _Aft2d_BndEdge_Header

#include <Aft2d_Edge.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_BndEdge
			: public Aft2d_Edge
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft2d_Edge>(*this);
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_BndEdge()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_BndEdge
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Aft2d_Node>, 2>& theNodes
			)
				: Aft2d_Edge(theIndex, theNodes)
			{}

			Aft2d_BndEdge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft2d_Node>, 2>&& theNodes
			)
				: Aft2d_Edge(theIndex, std::move(theNodes))
			{}


		public:


			// Public functions and operators [2/1/2023 Payvand]

			virtual Standard_Boolean IsSegment() const;

			TnbLegMesh_EXPORT Standard_Boolean IsBoundary() const override;

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft2d_BndEdge);

#endif // !_Aft2d_BndEdge_Header

