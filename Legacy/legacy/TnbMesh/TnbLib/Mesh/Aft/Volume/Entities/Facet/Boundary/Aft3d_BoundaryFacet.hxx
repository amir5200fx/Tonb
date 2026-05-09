#pragma once
#ifndef _Aft3d_BoundaryFacet_Header
#define _Aft3d_BoundaryFacet_Header

#include <Aft3d_Facet.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_BoundaryFacet
			: public Aft3d_Facet
		{

			/*Private Data*/


			// Private functions and operators [2/28/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_Facet>(*this);
			}

		public:

			// default constructor [2/28/2023 Payvand]

			Aft3d_BoundaryFacet()
			{}

			// constructors [2/28/2023 Payvand]

			Aft3d_BoundaryFacet
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Facet(theIndex, theNodes)
			{}

			Aft3d_BoundaryFacet
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Facet(theIndex, std::move(theNodes))
			{}

			// Public functions and operators [2/28/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Boolean IsBoundary() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_BoundaryFacet);

#endif // !_Aft3d_BoundaryFacet_Header
