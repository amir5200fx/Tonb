#include <Aft3d_Model.hxx>

#include <Aft_Tools.hxx>
#include <Entity3d_Box.hxx>

//template<>
//void tnbLib::Aft3d_Model::Import
//(
//	const std::vector<std::shared_ptr<Aft3d_Facet>>& theBoundaries,
//	const std::shared_ptr<Aft3d_MetricPrcsr>& theBoundaryMap
//)
//{
//	ElementCounter() = 0;
//
//	const auto nodes = Aft_Tools::RetrieveNodes(theBoundaries);
//
//	NodeCounter() = (Standard_Integer)nodes.size();
//	EdgeCounter() = Aft_Tools::CalcNbEdges(theBoundaries);
//	FacetCounter() = (Standard_Integer)theBoundaries.size();
//
//	CheckBoundary(GetBoundaryEntities());
//
//	const auto box = RetrieveBoundingBox(nodes);
//
//	// Set Searching Region
//	SetGeometryRegion(box.OffSet(0.01 * box.Diameter()));
//
//	// Insert To Front
//	InsertToGeometry(nodes);
//	InsertToPriority(GetBoundaryEntities());
//}