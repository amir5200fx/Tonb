#pragma once
#ifndef _Aft3d_InteriorFacet_Header
#define _Aft3d_InteriorFacet_Header

#include <Aft3d_Facet.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_InteriorFacet
			: public Aft3d_Facet
		{

			/*Private Data*/


			// Private functions and operators [3/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_Facet>(*this);
			}

		public:

			// default constructor [2/27/2023 Payvand]

			Aft3d_InteriorFacet()
			{}


			// constructors [2/27/2023 Payvand]

			explicit Aft3d_InteriorFacet(const Standard_Integer theIndex)
				: Aft3d_Facet(theIndex)
			{}


			Aft3d_InteriorFacet
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Facet(theIndex, theNodes)
			{}

			Aft3d_InteriorFacet
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Facet(theIndex, std::move(theNodes))
			{}


			// Public functions and operators [2/27/2023 Payvand]

			Standard_Boolean IsInterior() const override { return Standard_True; }

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_InteriorFacet);

#endif // !_Aft3d_InteriorFacet_Header
