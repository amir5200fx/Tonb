#include <PtdShapeFit2d_SingleScatterMap.hxx>

const unsigned int tnbLib::PtdShapeFit2d_SingleScatterMap::nb_regions(1);

Standard_Integer 
tnbLib::PtdShapeFit2d_SingleScatterMap::NbRegions() const
{
	return Standard_Integer(nb_regions);
}

std::shared_ptr<typename tnbLib::PtdShapeFit2d_SingleScatterMap::ptList>
tnbLib::PtdShapeFit2d_SingleScatterMap::Region(const Standard_Integer /*theIndex*/) const
{
	return thePnts_;
}

void tnbLib::PtdShapeFit2d_SingleScatterMap::SetPnts(const std::shared_ptr<ptList>& thePnts)
{
	thePnts_ = thePnts;
}

void tnbLib::PtdShapeFit2d_SingleScatterMap::SetPnts(std::shared_ptr<ptList>&& thePnts)
{
	thePnts_ = std::move(thePnts);
}