#include <GeoMesh2d_Background.hxx>

#include <MeshBase_Tools.hxx>
#include <GeoMesh2d_Data.hxx>

template<>
void tnbLib::GeoMesh2d_SingleBackground::ConnectTopology()
{
	if (const auto& mesh = this->Mesh())
	{
		if (mesh->Elements().size())
		{
			MeshBase_Tools::ConnectMesh(mesh->Elements());
		}
	}
}

namespace tnbLib
{

	Standard_Real Length(const Standard_Real H1, const Pnt2d& P1, const Pnt2d& P2)
	{
		return ((Standard_Real)1.0 / H1)*Distance(P1, P2);
	}

	template<>
	void GeoMesh2d_SingleBackground::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh2d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	)
	{
		if (Factor < 0 OR Factor > 1)
		{
			FatalErrorIn("void HvCorrection(const Standard_Real Factor, const Standard_Integer MaxInnerIteration = 5)")
				<< "Invalid HvCorrection's factor" << endl
				<< " - factor : " << Factor << endl
				<< abort(FatalError);
		}

		if (MaxInnerIteration < 1)
		{
			FatalErrorIn("void HvCorrection(const Standard_Real Factor, const Standard_Integer MaxInnerIteration = 5)")
				<< "Invalid HvCorrection's MaxInnerIteration" << endl
				<< " - MaxInnerIteration : " << MaxInnerIteration << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(base::Mesh());

		auto& sources = theSources_;
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			const auto& node = *x;

			auto edges = node.RetrieveEdges();
			for (int Iter = 1; Iter <= MaxInnerIteration; Iter++)
			{
				Standard_Boolean replaced = Standard_False;

				for (const auto& iedge : edges)
				{
					const auto& ptr = iedge.second;
					Debug_Null_Pointer(ptr.lock());
					const auto& edge = *ptr.lock();

					auto side = edge.Node1();
					if (side IS_EQUAL x) side = edge.Node0();

					auto length1 = Length(InterpolateAt(node.Coord()), node.Coord(), side->Coord());
					auto length2 = Length(InterpolateAt(side->Coord()), side->Coord(), node.Coord());

					auto val1 = sources[Index_Of(side->Index())] * ((Standard_Real)1.0 + Factor * length2);
					auto val2 = sources[Index_Of(node.Index())] * ((Standard_Real)1.0 + Factor * length1);

					if (val1 < sources[Index_Of(node.Index())])
					{
						replaced = Standard_True;
						sources[Index_Of(node.Index())] = val1;
					}

					if (val2 < sources[Index_Of(side->Index())])
					{
						replaced = Standard_True;
						sources[Index_Of(side->Index())] = val2;
					}
				}

				if (NOT replaced)
				{
					break;
				}
			}
		}

		for (int i = (int)nodes.size() - 1; i >= 0; i--)
		{
			const auto& x = nodes[i];

			Debug_Null_Pointer(x);
			const auto& node = *x;

			auto edges = node.RetrieveEdges();
			for (int Iter = 1; Iter <= MaxInnerIteration; Iter++)
			{
				Standard_Boolean replaced = Standard_False;

				for (const auto& iedge : edges)
				{
					const auto& ptr = iedge.second;
					Debug_Null_Pointer(ptr.lock());
					const auto& edge = *ptr.lock();

					auto side = edge.Node1();
					if (side IS_EQUAL x) side = edge.Node0();

					auto length1 = Length(InterpolateAt(node.Coord()), node.Coord(), side->Coord());
					auto length2 = Length(InterpolateAt(side->Coord()), side->Coord(), node.Coord());

					auto val1 = sources[Index_Of(side->Index())] * ((Standard_Real)1.0 + Factor * length2);
					auto val2 = sources[Index_Of(node.Index())] * ((Standard_Real)1.0 + Factor * length1);

					if (val1 < sources[Index_Of(node.Index())])
					{
						replaced = Standard_True;
						sources[Index_Of(node.Index())] = val1;
					}

					if (val2 < sources[Index_Of(side->Index())])
					{
						replaced = Standard_True;
						sources[Index_Of(side->Index())] = val2;
					}
				}

				if (NOT replaced)
				{
					break;
				}
			}
		}
	}
}