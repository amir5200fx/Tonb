#pragma once
#ifndef _Aft3d_InteriorEdge_Header
#define _Aft3d_InteriorEdge_Header

#include <Aft3d_Edge.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_InteriorEdge
			: public Aft3d_Edge
		{

			/*Private Data*/


			// Private functions and operators [6/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_Edge>(*this);
			}

		public:

			// default constructor [6/1/2023 Payvand]

			Aft3d_InteriorEdge()
			{}

			// constructors [6/1/2023 Payvand]

			Aft3d_InteriorEdge
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Edge(theIndex, theNodes)
			{}

			Aft3d_InteriorEdge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Edge(theIndex, std::move(theNodes))
			{}


			// Public functions and operators [6/1/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsInterior() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_InteriorEdge);

#endif // !_Aft3d_InteriorEdge_Header
