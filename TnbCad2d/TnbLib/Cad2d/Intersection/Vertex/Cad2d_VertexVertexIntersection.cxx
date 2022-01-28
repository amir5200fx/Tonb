#include <Cad2d_VertexVertexIntersection.hxx>

#include <Cad2d_IntsctEntity_Point.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Pln_Vertex.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Cad2d_VertexVertexIntersection::Perform()
{
	if (NOT Vtx0())
	{
		FatalErrorIn(FunctionSIG)
			<< " the vtx0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Vtx1())
	{
		FatalErrorIn(FunctionSIG)
			<< " the vtx1 is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& pt0 = Vtx0()->Coord();
	const auto& pt1 = Vtx1()->Coord();

	auto& entities = ChangeEntities();
	if (pt0.Distance(pt1) <= Tolerance())
	{
		auto ent0 = std::make_shared<Cad2d_IntsctEntity_Point>(1, Vtx0());
		auto ent1 = std::make_shared<Cad2d_IntsctEntity_Point>(2, Vtx1());

		auto paired = 
			std::make_shared<Cad2d_IntsctEntity_Pair>
			(1, std::move(ent0), std::move(ent1));

		entities.push_back(std::move(paired));
	}
	Change_IsDone() = Standard_True;
}