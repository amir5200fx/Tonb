#include <Marine_Model_SailTools.hxx>

#include <Entity2d_Triangulation.hxx>
#include <Geo2d_CdtDelTri.hxx>
#include <Geo_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Cad2d_MergePlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Edge.hxx>
#include <Marine_Models.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>
#include <gp_Pln.hxx>
#include <Poly_Triangulation.hxx>
#include <TopoDS_Face.hxx>

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Marine_Model_SailTools::LateralProjArea
(
	const std::shared_ptr<marineLib::Model_SurfaceSail>& theSail
)
{
	if (NOT theSail)
	{
		FatalErrorIn(FunctionSIG)
			<< " the sail model pointer is null" << endl
			<< abort(FatalError);
	}

	const auto& face = theSail->Face();
	auto poly = Cad_Tools::RetrieveTriangulation(face);
	if (NOT poly)
	{
		FatalErrorIn(FunctionSIG)
			<< "the face has no mesh!" << endl
			<< abort(FatalError);
	}
	auto triangulation3d = 
		Cad_Tools::Triangulation(*poly);

	gp_Pln yPlane(gp::Origin(), gp::DY());
	std::vector<Pnt2d> pnts;
	pnts.reserve(triangulation3d->NbPoints());
	for (const auto& x : triangulation3d->Points())
	{
		auto pt3 = Geo_Tools::ProjectToPlane_cgal(x, yPlane);
		Pnt2d pt2(pt3.X(), pt3.Z());
		pnts.push_back(std::move(pt2));
	}

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& indices = triangulation3d->Connectivity();
	tri->Points() = std::move(pnts);
	tri->Connectivity() = std::move(indices);

	Geo_Tools::MakeTrianglesCCW(tri);
	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Marine_Model_SailTools::GetMergedPlane
(
	const std::shared_ptr<marineLib::Model_LateralPlnSail>& theSail, 
	const Standard_Real theResolution, 
	const Standard_Real theRadius
)
{
	if (NOT theSail)
	{
		FatalErrorIn(FunctionSIG)
			<< " the sail model pointer is null" << endl
			<< abort(FatalError);
	}
	const auto& plane = theSail->Plane();
	if (NOT plane)
	{
		FatalErrorIn(FunctionSIG)
			<< " the sail has no plane!" << endl
			<< abort(FatalError);
	}

	Cad2d_MergePlane alg;
	alg.Info().radius = theRadius;
	alg.Info().resolution = theResolution;
	alg.LoadPlane(plane);

	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorith is not performed!");

	const auto& merged = alg.Merged();
	return std::move(merged);
}

void tnbLib::Marine_Model_SailTools::Triangulate
(
	const std::shared_ptr<marineLib::Model_LateralPlnSail>& theSail
)
{
	if (NOT theSail)
	{
		FatalErrorIn(FunctionSIG)
			<< " the sail model pointer is null" << endl
			<< abort(FatalError);
	}
	const auto& plane = theSail->Plane();
	if (NOT plane)
	{
		FatalErrorIn(FunctionSIG)
			<< " the sail has no plane!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	auto edges = plane->RetrieveEntities(Pln_EntityType::EDGE);
	Debug_If_Condition(edges.empty());
	polygons.reserve(edges.size());
	for (const auto& iter : edges)
	{
		auto e = std::dynamic_pointer_cast<Pln_Edge>(iter);
		Debug_Null_Pointer(e);
		auto mesh = e->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is not discretized!" << endl
				<< abort(FatalError);
		}
		if (NOT e->Sense())
		{
			mesh = std::make_shared<Entity2d_Polygon>(*e->Mesh());
			Debug_Null_Pointer(mesh);
			mesh->Reverse();
		}
		polygons.push_back(std::move(mesh));
	}
	
	std::vector<Pnt2d> pnts;
	for (const auto& iter : polygons)
	{
		Debug_Null_Pointer(iter);
		for (const auto& x : iter->Points())
		{
			pnts.push_back(x);
		}
	}

	Geo2d_CdtDelTri del(pnts, polygons);
	del.SetToHandleDegeneracy();
	del.Perform();

	Debug_If_Condition_Message(NOT del.IsDone(), "the algorithm is not performed!");

	auto tri = del.Data();
	theSail->SetTriangulation(std::move(tri));
}