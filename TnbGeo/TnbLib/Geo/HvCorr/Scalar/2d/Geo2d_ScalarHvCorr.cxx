#include <Geo2d_ScalarHvCorr.hxx>

#include <Geo_ScalarHvCorrInfo.hxx>
#include <Geo_GraphTools.hxx>
#include <Geo2d_Graph.hxx>
#include <Geo2d_SegmentGraphEdge.hxx>
#include <Geo2d_GraphNode.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::shared_ptr<tnbLib::Geo_ScalarHvCorrInfo> tnbLib::Geo2d_ScalarHvCorr::DEFAULT_INFO =
std::make_shared<tnbLib::Geo_ScalarHvCorrInfo>();

void tnbLib::Geo2d_ScalarHvCorr::Perform()
{
	if (NOT Graph())
	{
		FatalErrorIn(FunctionSIG)
			<< "no triangulation has been found." << endl
			<< abort(FatalError);
	}

	if (NOT LenFun)
	{
		FatalErrorIn(FunctionSIG)
			<< "no functions has been found." << endl
			<< abort(FatalError);
	}

	if (NOT SizeFunc)
	{
		FatalErrorIn(FunctionSIG)
			<< "no size function has been found." << endl
			<< abort(FatalError);
	}

	if (NOT CorrInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found." << endl
			<< abort(FatalError);
	}

	auto& sources = SourcesRef();
	const auto edges = Global_Tools::RetrieveValuesToList(Graph()->Edges());
	const auto nodes = Geo_GraphTools::RetrieveNodes(edges);
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		auto edges = x->RetrieveEdges();
		for (size_t Iter = 1; Iter <= CorrInfo()->MaxNbIters(); Iter++)
		{
			Standard_Boolean replaced = Standard_False;
			for (const auto& wied : edges)
			{
				auto e = wied.lock();
				Debug_Null_Pointer(e);

				auto seg = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(e);
				Debug_Null_Pointer(seg);

				auto side = seg->Node1();
				if (side IS_EQUAL x) side = seg->Node0();

				auto length1 = LenFun(SizeFunc(x->Coord()), x->Coord(), side->Coord());
				auto length2 = LenFun(SizeFunc(side->Coord()), side->Coord(), x->Coord());

				auto val1 = sources.at(Index_Of(side->Index()))*((Standard_Real)1.0 + CorrInfo()->Factor()*length2);
				auto val2 = sources.at(Index_Of(x->Index()))*((Standard_Real)1.0 + CorrInfo()->Factor()*length1);

				if (val1 < sources.at(Index_Of(x->Index())))
				{
					replaced = Standard_True;
					sources.at(Index_Of(x->Index())) = val1;
				}

				if (val2 < sources.at(Index_Of(side->Index())))
				{
					replaced = Standard_True;
					sources.at(Index_Of(side->Index())) = val2;
				}
			}

			if (NOT replaced)
			{
				break;
			}
		}
	}

	for (auto i = nodes.size() - 1; i >= 0; i--)
	{
		const auto& x = nodes.at(i);
		Debug_Null_Pointer(x);

		auto edges = x->RetrieveEdges();
		for (size_t Iter = 1; Iter <= CorrInfo()->MaxNbIters(); Iter++)
		{
			Standard_Boolean replaced = Standard_False;
			for (const auto& wied : edges)
			{
				auto e = wied.lock();
				Debug_Null_Pointer(e);

				auto seg = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(e);
				Debug_Null_Pointer(seg);

				auto side = seg->Node1();
				if (side IS_EQUAL x) side = seg->Node0();

				auto length1 = LenFun(SizeFunc(x->Coord()), x->Coord(), side->Coord());
				auto length2 = LenFun(SizeFunc(side->Coord()), side->Coord(), x->Coord());

				auto val1 = sources.at(Index_Of(side->Index()))*((Standard_Real)1.0 + CorrInfo()->Factor()*length2);
				auto val2 = sources.at(Index_Of(x->Index()))*((Standard_Real)1.0 + CorrInfo()->Factor()*length1);

				if (val1 < sources.at(Index_Of(x->Index())))
				{
					replaced = Standard_True;
					sources.at(Index_Of(x->Index())) = val1;
				}

				if (val2 < sources.at(Index_Of(side->Index())))
				{
					replaced = Standard_True;
					sources.at(Index_Of(side->Index())) = val2;
				}
			}
			if (NOT replaced)
			{
				break;
			}
		}
	}

	Change_IsDone() = Standard_True;
}