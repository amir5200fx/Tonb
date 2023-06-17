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

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Edge>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::PairedEdge3() const
{
	return std::get<0>(thePairedEdges_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Edge>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::PairedEdge4() const
{
	return std::get<1>(thePairedEdges_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Edge>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::PairedEdge5() const
{
	return std::get<2>(thePairedEdges_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Facet>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::CreatedFacet0() const
{
	return std::get<0>(theCreatedFacets_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Facet>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::CreatedFacet1() const
{
	return std::get<1>(theCreatedFacets_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Facet>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::CreatedFacet2() const
{
	return std::get<2>(theCreatedFacets_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Edge>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::CreatedEdge3() const
{
	return std::get<0>(theCreatedEdges_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Edge>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::CreatedEdge4() const
{
	return std::get<1>(theCreatedEdges_);
}

inline const std::shared_ptr<tnbLib::legLib::Aft3d_Edge>&
tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::CreatedEdge5() const
{
	return std::get<2>(theCreatedEdges_);
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
	Debug_If_Condition(theLen <= gp::Resolution());
	theMaxElemLength_ = theLen;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetLocRadius(const Standard_Real theRadius)
{
	Debug_If_Condition(theRadius <= gp::Resolution());
	theLocalRadius_ = theRadius;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetSearchRadius(const Standard_Real theRadius)
{
	Debug_If_Condition(theRadius <= gp::Resolution());
	theSearchRadius_ = theRadius;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetElementSize(const Standard_Real theSize)
{
	Debug_If_Condition(theSize <= gp::Resolution());
	theSize_ = theSize;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCycleMode(const cycleMode mode)
{
	theCycleMode_ = mode;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetNodeMode(const nodeMode mode)
{
	theNodeMode_ = mode;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetPairedFacet0
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	std::get<0>(thePairedFacets_) = theFacet;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetPairedFacet1
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	std::get<1>(thePairedFacets_) = theFacet;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetPairedFacet2
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	std::get<2>(thePairedFacets_) = theFacet;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetPairedEdge3
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	std::get<0>(thePairedEdges_) = theEdge;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetPairedEdge4
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	std::get<1>(thePairedEdges_) = theEdge;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetPairedEdge5
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	std::get<2>(thePairedEdges_) = theEdge;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCreatedFacet0
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	std::get<0>(theCreatedFacets_) = theFacet;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCreatedFacet1
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	std::get<1>(theCreatedFacets_) = theFacet;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCreatedFacet2
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	std::get<2>(theCreatedFacets_) = theFacet;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCreatedEdge3
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	std::get<0>(theCreatedEdges_) = theEdge;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCreatedEdge4
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	std::get<1>(theCreatedEdges_) = theEdge;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetCreatedEdge5
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	std::get<2>(theCreatedEdges_) = theEdge;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	theElement_ = theElement;
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::SetElement
(
	std::shared_ptr<Aft3d_Element>&& theElement
)
{
	theElement_ = std::move(theElement);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cycleSpecs::Reset()
{
	theCandidateSize_ = 0;

	theSize_ = 0;

	theLocalRadius_ = 0;
	theSearchRadius_ = 0;
	theMaxElemLength_ = 0;

	theCoord_ = Pnt3d::null;

	theRegion_ = nullptr;

	theTemp_ = nullptr;
	theValid_ = nullptr;

	theCurrent_ = nullptr;
	theElement_ = nullptr;

	thePairedFacets_.at(0) = nullptr;
	thePairedFacets_.at(1) = nullptr;
	thePairedFacets_.at(2) = nullptr;

	theCreatedFacets_.at(0) = nullptr;
	theCreatedFacets_.at(1) = nullptr;
	theCreatedFacets_.at(2) = nullptr;

	thePairedEdges_.at(0) = nullptr;
	thePairedEdges_.at(1) = nullptr;
	thePairedEdges_.at(2) = nullptr;

	theCreatedEdges_.at(0) = nullptr;
	theCreatedEdges_.at(1) = nullptr;
	theCreatedEdges_.at(2) = nullptr;
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

inline void tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::InsertToUncertainty
(const std::shared_ptr<Aft3d_Facet>& theFront)
{
	auto [iter, cond] = theUncertainty_.insert(theFront);
	if (NOT cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found." << endl
			<< abort(FatalError);
	}
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::InsertToCertainty
(const std::shared_ptr<Aft3d_Facet>& theFront)
{
	auto [iter, cond] = theCertainty_.insert(theFront);
	if (NOT cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found." << endl
			<< abort(FatalError);
	}
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::RemoveFromUncertainty
(const std::shared_ptr<Aft3d_Facet>& theFront)
{
	auto iter = theUncertainty_.find(theFront);
	if (iter IS_EQUAL theUncertainty_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "couldn't find the front in the set." << endl
			<< abort(FatalError);
	}
	theUncertainty_.erase(iter);
}

inline void tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::RemoveFromCertainty
(const std::shared_ptr<Aft3d_Facet>& theFront)
{
	auto iter = theCertainty_.find(theFront);
	if (iter IS_EQUAL theCertainty_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "couldn't find the front in the set." << endl
			<< abort(FatalError);
	}
	theCertainty_.erase(iter);
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

inline void tnbLib::legLib::Aft3d_VolumeCore::meshData::Insert
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& elemnts = *theElements_;
	auto [iter, cond] = elemnts.insert(theElement);
	if (NOT cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found." << endl
			<< abort(FatalError);
	}
}

inline void tnbLib::legLib::Aft3d_VolumeCore::meshData::Insert
(
	std::shared_ptr<Aft3d_Element>&& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& elemnts = *theElements_;
	auto [iter, cond] = elemnts.insert(std::move(theElement));
	if (NOT cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found." << endl
			<< abort(FatalError);
	}
}

inline void tnbLib::legLib::Aft3d_VolumeCore::meshData::Remove
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& elemnts = *theElements_;
	auto iter = elemnts.find(theElement);
	if (iter IS_EQUAL elemnts.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element has not been found in the set." << endl
			<< abort(FatalError);
	}
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