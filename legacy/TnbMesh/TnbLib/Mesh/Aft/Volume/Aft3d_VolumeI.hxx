#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
inline Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::frontHandler::IsCurrentEmpty() const
{
	return Standard_Boolean(theCurrentLev_.empty());
}

inline Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::frontHandler::IsNextEmtpy() const
{
	return Standard_Boolean(theNextLev_.empty());
}

inline Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::frontHandler::GetFront
(
	std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	return theFronts_.RetrieveFromPriority(theFacet);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::InsertToCurrent
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	theCurrentLev_.insert(theFacet);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::InsertToNext
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	theNextLev_.insert(theFacet);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::InsertToFronts
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts
)
{
	theFronts_.InsertToPriority(theFronts);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::ClearCurrent()
{
	theCurrentLev_.clear();
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::ClearNext()
{
	theNextLev_.clear();
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::SetCurrentLev(const Standard_Integer n)
{
	theLevel_ = n;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::frontHandler::SetMaxLevel(const Standard_Integer n)
{
	theMaxId_ = n;
}

inline std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Facet>>
tnbLib::legLib::Aft3d_VolumeCore::frontHandler::RetrieveCurrentLevel() const
{
	std::vector<std::shared_ptr<Aft3d_Facet>> facets;
	std::copy(theCurrentLev_.begin(), theCurrentLev_.end(), std::back_inserter(facets));
	return std::move(facets);
}

inline std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Facet>>
tnbLib::legLib::Aft3d_VolumeCore::frontHandler::RetrieveNexLevel() const
{
	std::vector<std::shared_ptr<Aft3d_Facet>> facets;
	std::copy(theNextLev_.begin(), theNextLev_.end(), std::back_inserter(facets));
	return std::move(facets);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Facet>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::PairedFacet0() const
{
	return std::get<0>(thePairedFacets_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Facet>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::PairedFacet1() const
{
	return std::get<1>(thePairedFacets_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Facet>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::PairedFacet2() const
{
	return std::get<2>(thePairedFacets_);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCoord(const Pnt3d& theCoord)
{
	theCoord_ = theCoord;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCoord(Pnt3d&& theCoord)
{
	theCoord_ = std::move(theCoord);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetTempNode
(
	const std::shared_ptr<Aft3d_Node>& theNode
)
{
	theTemp_ = theNode;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetValidNode
(
	const std::shared_ptr<Aft3d_Node>& theNode
)
{
	theValid_ = theNode;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetRegion
(
	const std::shared_ptr<Entity3d_Box>& theRegion
)
{
	theRegion_ = theRegion;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetRegion
(
	std::shared_ptr<Entity3d_Box>&& theRegion
)
{
	theRegion_ = std::move(theRegion);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCurrent
(
	const std::shared_ptr<Aft3d_Facet>& theCurrent
)
{
	theCurrent_ = theCurrent;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCurrent
(
	std::shared_ptr<Aft3d_Facet>&& theCurrent
)
{
	theCurrent_ = std::move(theCurrent);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCandidateSize(const Standard_Integer n)
{
	theCandidateSize_ = n;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetMaxElmLength(const Standard_Real theLen)
{
	theMaxElemLength_ = theLen;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetLocRadius(const Standard_Real theRadius)
{
	theLocalRadius_ = theRadius;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCycleMode(const cycleMode mode)
{
	theCycleMode_ = mode;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetNodeMode(const nodeMode mode)
{
	theNodeMode_ = mode;
}

inline Standard_Boolean
tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::IsUncertaintyEmpty() const
{
	return Standard_Boolean(theUncertainty_.empty());
}

inline Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::IsCertaintyEmpty() const
{
	return Standard_Boolean(theCertainty_.empty());
}

inline std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Facet>>
tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::RetrieveUncertainties() const
{
	std::vector<std::shared_ptr<Aft3d_Facet>> facets;
	std::copy(theUncertainty_.begin(), theUncertainty_.end(), std::back_inserter(facets));
	return std::move(facets);
}

inline std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Facet>>
tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::RetrieveCertainties() const
{
	std::vector<std::shared_ptr<Aft3d_Facet>> facets;
	std::copy(theCertainty_.begin(), theCertainty_.end(), std::back_inserter(facets));
	return std::move(facets);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::ClearUncertainty()
{
	theUncertainty_.clear();
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::ClearCertainty()
{
	theCertainty_.clear();
}

inline Standard_Integer 
tnbLib::legLib::Aft3d_VolumeCore::meshData::NbElements() const
{
	Debug_Null_Pointer(theElements_);
	return Standard_Integer(theElements_->size());
}

inline void tnbLib::legLib::Aft3d_VolumeCore::meshData::SetNbNodes(const Standard_Integer n)
{
	theNbNodes_ = n;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::meshData::Clear()
{
	Debug_Null_Pointer(theElements_);
	theElements_->clear();
}

inline Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsNewNode() const
{
	return (Standard_Boolean)(CycleInfo.ValidNode() IS_EQUAL CycleInfo.TempNode());
}