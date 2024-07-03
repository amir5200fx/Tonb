#pragma once
#ifndef _Aft2d_SegmentEdge_Header
#define _Aft2d_SegmentEdge_Header

#include <Aft2d_BndEdge.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_SegmentEdge
			: public Aft2d_BndEdge
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft2d_BndEdge>(*this);
			}

		public:

			// default constructor [2/1/2023 Payvand]

			Aft2d_SegmentEdge()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_SegmentEdge
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft2d_Node>, 2>& theNodes
			)
				: Aft2d_BndEdge(theIndex, theNodes)
			{}

			Aft2d_SegmentEdge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft2d_Node>, 2>&& theNodes
			)
				: Aft2d_BndEdge(theIndex, std::move(theNodes))
			{}


			// Public functions and operators [2/1/2023 Payvand]


			TnbLegMesh_EXPORT Standard_Boolean IsSegment() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft2d_SegmentEdge);

#endif // !_Aft2d_SegmentEdge_Header
