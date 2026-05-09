#pragma once
template<class ElementType, tnbLib::Mesh_ElementType ElmType>
inline void tnbLib::Mesh_ElementAdaptor<ElementType, ElmType>::SetNeighbor
(
	const Standard_Integer theIndex,
	const std::shared_ptr<ElementType>& theElement
)
{
	theNeighbors_.at(theIndex) = theElement;
}