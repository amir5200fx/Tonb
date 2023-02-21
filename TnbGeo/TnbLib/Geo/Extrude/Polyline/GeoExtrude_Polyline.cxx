#include <GeoExtrude_Polyline.hxx>

#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>

void tnbLib::GeoExtrude_Polyline::Perform()
{
	if (NOT Polyline())
	{
		FatalErrorIn(FunctionSIG)
			<< "no polyline has been loaded." << endl
			<< abort(FatalError);
	}

	std::vector<Pnt3d> pnts;
	pnts.reserve(3 * Polyline()->NbPoints());

	std::vector<Pnt3d> layer0, layer1, layer2;
	layer0.reserve(Polyline()->NbPoints());
	layer1.reserve(Polyline()->NbPoints());
	layer2.reserve(Polyline()->NbPoints());

	for (const auto& x : Polyline()->Points())
	{
		Pnt3d p0(x.X(), x.Y(), Z1());
		Pnt3d p1(x.X(), x.Y(), 0);
		Pnt3d p2(x.X(), x.Y(), Z0());

		layer0.push_back(std::move(p0));
		layer1.push_back(std::move(p1));
		layer2.push_back(std::move(p2));
	}
	for (auto& x : layer0)
	{
		pnts.push_back(std::move(x));
	}
	layer0.clear();
	for (auto& x : layer1)
	{
		pnts.push_back(std::move(x));
	}
	layer1.clear();
	for (auto& x : layer2)
	{
		pnts.push_back(std::move(x));
	}
	layer2.clear();
	const auto n = Polyline()->NbPoints();
	std::vector<connectivity::triple> indices;
	for (int m = 1; m < 3; m++)
	{
		for (int i = 1; i <= n; i++)
		{
			{// triangle 1 [2/19/2023 Payvand]
				auto v0 = (m - 1) * n + i;
				auto v1 = m * n + i;
				auto v2 = m * n + i % n + 1;

				connectivity::triple t;
				t.Value(0) = v0;
				t.Value(1) = v1;
				t.Value(2) = v2;

				indices.push_back(std::move(t));
			}
			{// triangle 2 [2/19/2023 Payvand]
				auto v0 = (m - 1) * n + i;
				auto v1 = m * n + i % n + 1;
				auto v2 = (m - 1) * n + i % n + 1;

				connectivity::triple t;
				t.Value(0) = v0;
				t.Value(1) = v1;
				t.Value(2) = v2;

				indices.push_back(std::move(t));
			}
		}
	}
	auto tris = std::make_shared<Entity3d_Triangulation>(std::move(pnts), std::move(indices));
	theMesh_ = std::move(tris);
	Change_IsDone() = Standard_True;
}