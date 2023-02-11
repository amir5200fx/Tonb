#pragma once
#ifndef _PtdShapeFit2d_SingleScatterMap_Header
#define _PtdShapeFit2d_SingleScatterMap_Header

#include <PtdShapeFit2d_ScatterMap.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_SingleScatterMap
		: public PtdShapeFit2d_ScatterMap
	{

	public:

		using PtdShapeFit2d_ScatterMap::ptList;

	private:

		/*Private Data*/

		std::shared_ptr<ptList> thePnts_;

		
		// Private functions and operators [2/10/2023 Payvand]

		TNB_SERIALIZATION(TnbPtdShapeFit_EXPORT);

	public:

		static TnbPtdShapeFit_EXPORT const unsigned int nb_regions;

		// default constructor [2/10/2023 Payvand]

		PtdShapeFit2d_SingleScatterMap()
		{}

		// constructors [2/10/2023 Payvand]

		explicit PtdShapeFit2d_SingleScatterMap(const std::shared_ptr<ptList>& thePnts)
			: thePnts_(thePnts)
		{}

		PtdShapeFit2d_SingleScatterMap(std::shared_ptr<ptList>&& thePnts)
			: thePnts_(std::move(thePnts))
		{}


		// Public functions and operators [2/10/2023 Payvand]

		const auto& Pnts() const
		{
			return thePnts_;
		}

		auto& PntsRef()
		{
			return thePnts_;
		}

		TnbPtdShapeFit_EXPORT Standard_Integer 
			NbRegions() const override;

		TnbPtdShapeFit_EXPORT std::shared_ptr<ptList> 
			Region(const Standard_Integer theIndex) const override;

		TnbPtdShapeFit_EXPORT void SetPnts(const std::shared_ptr<ptList>&);
		TnbPtdShapeFit_EXPORT void SetPnts(std::shared_ptr<ptList>&&);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdShapeFit2d_SingleScatterMap);

#endif // !_PtdShapeFit2d_SingleScatterMap_Header
