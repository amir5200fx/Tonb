#include <Cad2d_PolygonTrim.hxx>

//#include <Geo_MxCifQuadtree.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Cad2d_PolygonTrim::Cad2d_PolygonTrim()
{
}

tnbLib::Cad2d_PolygonTrim::Cad2d_PolygonTrim
(
	const std::shared_ptr<edgeList>& theEdges
)
	: theEdges_(theEdges)
{
}

//void tnbLib::Cad2d_PolygonTrim::Perform
//(
//	const Standard_Integer theTol
//)
//{
//	if (NOT Edges())
//	{
//		FatalErrorIn("void tnbLib::Cad2d_PolygonTrim::Perform()")
//			<< "the edge list is not loaded!" << endl
//			<< abort(FatalError);
//	}
//
//	Geo_MxCifQuadtree<Pln_Edge> regTree;
//	for (const auto& x : *Edges())
//	{
//		Debug_Null_Pointer(x);
//		regTree.Insert(x);
//	}
//
//
//}