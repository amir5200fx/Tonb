#include <Cad2d_VertexVertexIntersection.hxx>

#include <Cad2d_IntsctEntity_Point.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Pln_Vertex.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Cad2d_VertexVertexIntersection> 
tnbLib::Cad2d_VertexVertexIntersection::operator()
(
	const std::shared_ptr<Pln_Vertex>& theVtx0,
	const std::shared_ptr<Pln_Vertex>& theVtx1,
	const Standard_Real theTol
	) const
{
	auto ent = Cad2d_VertexVertexIntersection::Intersect(theVtx0, theVtx1, theTol);
	return std::move(ent);
}

std::shared_ptr<tnbLib::Cad2d_VertexVertexIntersection> 
tnbLib::Cad2d_VertexVertexIntersection::Intersect
(
	const std::shared_ptr<Pln_Vertex>& theVtx0,
	const std::shared_ptr<Pln_Vertex>& theVtx1,
	const Standard_Real theTol
)
{
	if (NOT theVtx0)
	{
		FatalErrorIn(FunctionSIG)
			<< " the vtx0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT theVtx1)
	{
		FatalErrorIn(FunctionSIG)
			<< " the vtx1 is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& pt0 = theVtx0->Coord();
	const auto& pt1 = theVtx1->Coord();

	auto ent = std::make_shared<Cad2d_VertexVertexIntersection>(theVtx0, theVtx1);
	Debug_Null_Pointer(ent);

	ent->SetTolerance(theTol);
	auto& entities = ent->EntitiesRef();
	if (pt0.Distance(pt1) <= theTol)
	{
		auto ent0 = std::make_shared<Cad2d_IntsctEntity_Point>(1, theVtx0);
		auto ent1 = std::make_shared<Cad2d_IntsctEntity_Point>(2, theVtx1);

		auto paired =
			std::make_shared<Cad2d_IntsctEntity_Pair>
			(1, std::move(ent0), std::move(ent1));

		entities.push_back(std::move(paired));
	}
	return std::move(ent);
}