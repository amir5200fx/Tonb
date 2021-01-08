#include <GeoMesh2d_MetricBackground.hxx>

#include <Mesh2d_Node.hxx>

namespace tnbLib
{

	template<>
	void GeoMesh2d_MetricBackground::HvCorrection
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

		auto& Sources = theSources_;

		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			const auto& node = *x;

			auto edges = node.RetrieveEdges();
			auto V1 = node.Index();

			for (int Iter = 1; Iter <= MaxInnerIteration; Iter++)
			{
				for (const auto& iedge : edges)
				{
					const auto& ptr = iedge.second;
					Debug_Null_Pointer(ptr.lock());
					const auto& edge = *ptr.lock();

					auto V2 = edge.Node0()->Index();
					if (V2 IS_EQUAL V1) V2 = edge.Node1()->Index();

					auto length1 = Entity2d_Metric1::Distance(nodes[Index_Of(V1)]->Coord(), nodes[Index_Of(V2)]->Coord(), Sources[Index_Of(V1)]);
					auto length2 = Entity2d_Metric1::Distance(nodes[Index_Of(V1)]->Coord(), nodes[Index_Of(V2)]->Coord(), Sources[Index_Of(V2)]);

					Standard_Real Down1 = 1.0 + Factor * length1;
					Standard_Real Down2 = 1.0 + Factor * length2;

					Standard_Real Gama1 = 1.0 / (Down1*Down1);
					Standard_Real Gama2 = 1.0 / (Down2*Down2);

					Sources[Index_Of(V1)] = Entity2d_Metric1::IntersectionPD(Sources[Index_Of(V1)], Gama2*Sources[Index_Of(V2)]);
					Sources[Index_Of(V2)] = Entity2d_Metric1::IntersectionPD(Sources[Index_Of(V2)], Gama1*Sources[Index_Of(V1)]);
				}
			}
		}
	}
}