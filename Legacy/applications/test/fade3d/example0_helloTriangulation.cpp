#include <Fade_3D.h>
#include <stdio.h>

#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_Box.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

using namespace FADE3D;
using namespace tnbLib;

auto getPoint3d(const Pnt3d& p)
{
	Point3 pt(p.X(), p.Y(), p.Z());
	return std::move(pt);
}

static auto GetTets
(
	const std::vector<FADE3D::Point3*>& thePoints,
	const std::vector<FADE3D::Tet3*>& theTets
)
{
	std::vector<Pnt3d> pts;
	pts.reserve(thePoints.size());
	int k = 0;
	for (const auto& x : thePoints)
	{
		x->customIndex = ++k;
		Pnt3d pt(x->x(), x->y(), x->z());
		pts.push_back(std::move(pt));
	}

	std::vector<connectivity::quadruple> indices;
	indices.reserve(theTets.size());
	k = 0;
	for (const auto& x : theTets)
	{
		FADE3D::Point3* p0;
		FADE3D::Point3* p1;
		FADE3D::Point3* p2;
		FADE3D::Point3* p3;
		x->getCorners(p0, p1, p2, p3);
		x->setCustomIndex(++k);

		connectivity::quadruple q;
		q.Value(0) = p0->customIndex;
		q.Value(1) = p1->customIndex;
		q.Value(2) = p2->customIndex;
		q.Value(3) = p3->customIndex;

		indices.push_back(std::move(q));
	}

	auto tets = std::make_shared<Entity3d_Tetrahedralization>(std::move(pts), std::move(indices));
	return std::move(tets);
}

int example0_main()
{
	std::cout<<"\n";
	std::cout<<"example0: HelloTriangulation - 10 lines of code\n";
	std::cout<<"* Triangulate 4 points\n";
	std::cout<<"* Visualize the result\n\n";

	// Create a triangulation
	Fade_3D dt;

	// Create and insert 4 points
	/*Point3 p0(0.0,0.0,0.0);
	Point3 p1(1.0,0.0,0.0);
	Point3 p2(0.5,2.0,0.0);
	Point3 p3(0.5,0.5,1.0);
	dt.insert(p0);
	dt.insert(p1);
	dt.insert(p2);
	dt.insert(p3);*/

	Entity3d_Box b(Pnt3d(-1.1, -5.1, -0.1), Pnt3d(1.0, 1.0, 1.0));
	std::vector<Point3> vInpts;
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Fwd_SW)));
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Fwd_SE)));
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Fwd_NE)));
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Fwd_NW)));

	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Aft_SW)));
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Aft_SE)));
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Aft_NE)));
	vInpts.push_back(getPoint3d(b.Corner(Box3d_PickAlgorithm_Aft_NW)));

	dt.insert(vInpts);

	std::vector<FADE3D::Tet3*> vTets;
	std::vector<FADE3D::Point3*> vertices;

	dt.getTetrahedra(vTets);
	dt.getVertices(vertices);

	auto tets = GetTets(vertices, vTets);

	OFstream myFile("tets.plt");
	tets->ExportToPlt(myFile);
	// Draw a file for the Geomview viewer
	//dt.show("example0.list");
	return 0;
}

