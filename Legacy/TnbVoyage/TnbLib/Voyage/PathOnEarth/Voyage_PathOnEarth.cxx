#include <Voyage_PathOnEarth.hxx>

#include <VoyageGeo_Earth.hxx>
#include <VoyageGeo_Path2.hxx>
#include <Cad_GeomSurface.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	auto RetrievePath3d(const Cad_GeomSurface& theSurface, const Entity2d_Polygon& thePath)
	{
		std::vector<Pnt3d> coords;
		coords.reserve(thePath.NbPoints());
		for (const auto& x : thePath.Points())
		{
			auto pt3d = theSurface.Value(x);
			coords.push_back(std::move(pt3d));
		}
		auto path = std::make_shared<Entity3d_Polygon>(std::move(coords), 0);
		return std::move(path);
	}
}

void tnbLib::Voyage_PathOnEarth::Perform()
{
	if (NOT Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "no earth has been found." << endl
			<< abort(FatalError);
	}
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG)
			<< "no path has been found." << endl
			<< abort(FatalError);
	}
	const auto surface = Earth()->Surface();
	const auto& path = Path();
	for (const auto& x : path->Curves())
	{
		Debug_Null_Pointer(x);
		const auto& mesh2d = x->Mesh();
		if (NOT mesh2d)
		{
			FatalErrorIn(FunctionSIG)
				<< "the path is no discretized." << endl
				<< abort(FatalError);
		}
		auto path3d = RetrievePath3d(*surface, *mesh2d);
		thePath3D_.push_back(std::move(path3d));
	}
	Change_IsDone() = Standard_True;
}