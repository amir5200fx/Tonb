#pragma once
#ifndef _PtdShapeFit2d_AirfoilScatterMap_BothMH102Surf_Header
#define _PtdShapeFit2d_AirfoilScatterMap_BothMH102Surf_Header

#include <PtdShapeFit2d_AirfoilScatterMap_MH102.hxx>

namespace tnbLib
{

	namespace airfoilScatterMapLib
	{

		class BothMH102Surf
			: public PtdShapeFit2d_AirfoilScatterMap_MH102
		{

		public:

			using PtdShapeFit2d_ScatterMap::ptList;

		private:

			/*Private Data*/

			// Private functions and operators [4/30/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilScatterMap_MH102>(*this);
			}

		public:

			static TnbPtdShapeFit_EXPORT const unsigned int nb_regions;

			// default constructor [4/30/2023 Payvand]

			BothMH102Surf()
			{}

			// constructors [4/30/2023 Payvand]

			// Public functions and operators [4/30/2023 Payvand]

			TnbPtdShapeFit_EXPORT Standard_Integer NbRegions() const override;

			TnbPtdShapeFit_EXPORT std::shared_ptr<ptList>
				Region(const Standard_Integer theIndex) const override;

			TnbPtdShapeFit_EXPORT std::vector<std::pair<std::shared_ptr<Pln_Curve>, std::shared_ptr<ptList>>>
				RetrieveCurves(const std::shared_ptr<Cad2d_Plane>&) const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::airfoilScatterMapLib::BothMH102Surf);

#endif // !_PtdShapeFit2d_AirfoilScatterMap_BothMH102Surf_Header
