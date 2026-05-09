#include <Cad2d_MergePlane.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <Merge2d_Chain.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Cad2d_MergePlane::mergeInfo::mergeInfo()
	: resolution(1.0E-3)
	, radius(1.0E-6)
{
	//- empty body
}

void tnbLib::Cad2d_MergePlane::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< " no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& edges = Plane()->RetrieveEntities(Pln_EntityType::EDGE);
	std::vector<std::shared_ptr<Entity2d_Chain>> chains;
	chains.reserve(edges.size());
	for (const auto& x : edges)
	{
		auto edge = std::dynamic_pointer_cast<Pln_Edge>(x);
		Debug_Null_Pointer(edge);

		const auto& mesh = edge->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is not discretized!" << endl
				<< abort(FatalError);
		}

		if (NOT edge->Sense())
		{
			auto chain = Geo_Tools::RetrieveChain(mesh->Reversed());
			chains.push_back(std::move(chain));
		}
		else
		{
			auto chain = Geo_Tools::RetrieveChain(*mesh);
			chains.push_back(std::move(chain));
		}	
	}

	Merge2d_Chain alg;
	alg.Import(chains);
	alg.InfoAlg().SetRadius(Info().radius);
	alg.InfoAlg().SetResolution(Info().resolution);

	alg.Perform();

	Debug_If_Condition_Message(NOT alg.IsDone(), "the merging algorithm is not performed!");

	theMerged_ = alg.Merged();

	Change_IsDone() = Standard_True;
}