#include <Geo3d_DelTri_Fade3d.hxx>

#include <Entity3d_Tetrahedralization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fade3d/Fade_3D.h>

namespace tnbLib
{

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
			Debug_Null_Pointer(x);
			x->customIndex = ++k;
			Pnt3d pt(x->x(), x->y(), x->z());
			pts.push_back(std::move(pt));
		}

		std::vector<connectivity::quadruple> indices;
		indices.reserve(theTets.size());
		k = 0;
		for (const auto& x : theTets)
		{
			Debug_Null_Pointer(x);

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
}

void tnbLib::fadeLib::Geo3d_DelTri::Perform()
{
	if (Points().size() < 4)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough nb. of points." << endl
			<< abort(FatalError);
	}
	std::vector<FADE3D::Point3> pts;
	pts.reserve(Points().size());
	for (const auto& x : Points())
	{
		FADE3D::Point3 pt(x.X(), x.Y(), x.Z());
		pts.push_back(std::move(pt));
	}

	FADE3D::Fade_3D Dt;
	Dt.insert(pts);

	std::vector<FADE3D::Tet3*> vTets;
	std::vector<FADE3D::Point3*> vertices;

	Dt.getTetrahedra(vTets);
	Dt.getVertices(vertices);

	auto myTets = GetTets(vertices, vTets);
	/*OFstream myFile("tets.plt");
	myTets->ExportToPlt(myFile);*/
	theTriangulation_ = std::move(myTets);

	Change_IsDone() = Standard_True;
}