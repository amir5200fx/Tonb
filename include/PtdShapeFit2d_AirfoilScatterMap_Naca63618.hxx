#pragma once
#ifndef _PtdShapeFit2d_AirfoilScatterMap_Naca63618_Header
#define _PtdShapeFit2d_AirfoilScatterMap_Naca63618_Header
#include <PtdShapeFit2d_AirfoilScatterMap.hxx>

namespace tnbLib
{
	namespace airfoilScatterMapLib
	{
		class Naca63618
			: public PtdShapeFit2d_AirfoilScatterMap
		{
			/*Private Data*/

			// Private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilScatterMap>(*this);
			}

		public:

			using PtdShapeFit2d_ScatterMap::ptList;

			static TnbPtdShapeFit_EXPORT const unsigned int nb_regions;

			// default constructor
			Naca63618() = default;

			// constructors

			// Public functions and operators

			TnbPtdShapeFit_EXPORT Standard_Integer NbRegions() const override;
			TnbPtdShapeFit_EXPORT std::shared_ptr<ptList> Region(const Standard_Integer theIndex) const override;
			TnbPtdShapeFit_EXPORT std::vector<std::pair<std::shared_ptr<Pln_Curve>, std::shared_ptr<ptList>>>
				RetrieveCurves(const std::shared_ptr<Cad2d_Plane>&) const override;
		};
	}
}
BOOST_CLASS_EXPORT_KEY(tnbLib::airfoilScatterMapLib::Naca63618);
#endif