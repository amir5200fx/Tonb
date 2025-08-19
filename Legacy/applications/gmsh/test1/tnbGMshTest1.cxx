#include <GMesh_Lib.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

using namespace tnbLib;

int main()
{

	GMesh_Lib::Initialize();

	GMesh_Lib::AddModel("t2");

	Standard_Real lc = 1.0e-2;

	auto p1 = GMesh_Lib::AddPoint(Pnt3d(0, 0, 0), lc, 1);
	auto p2 = GMesh_Lib::AddPoint(Pnt3d(0.1, 0.0, 0.0), lc, 2);
	auto p3 = GMesh_Lib::AddPoint(Pnt3d(0.1, 0.3, 0.0), lc, 3);

	auto p4 = GMesh_Lib::AddPoint(Pnt3d(0.0, 0.3, 0.0), lc, 4);

	auto l1 = GMesh_Lib::AddLine(p1, p2, 1);
	auto l2 = GMesh_Lib::AddLine(p3, p2, 2);
	auto l3 = GMesh_Lib::AddLine(p3, p4, 3);
	auto l4 = GMesh_Lib::AddLine(p4, p1, 4);

	auto w1 = GMesh_Lib::AddWire({ l4,l1,-l2,l3 }, 1);

	auto pl1 = GMesh_Lib::AddPlane({ w1 }, 1);

	GMesh_Lib::SynchronizeModel();

	auto p5 = GMesh_Lib::AddPoint(Pnt3d(0, 0.4, 0.0), lc, 5);
	auto l5 = GMesh_Lib::AddLine(p4, p5, 5);

	// But Gmsh also provides tools to transform (translate, rotate, etc.)
  // elementary entities or copies of elementary entities.  Geometrical
  // transformations take a vector of pairs of integers as first argument, which
  // contains the list of entities, represented by (dimension, tag) pairs.  For
  // example, the point 5 (dimension=0, tag=5) can be moved by 0.02 to the left
  // (dx=-0.02, dy=0, dz=0) with
	GMesh_Lib::Translate({ {0, p5} }, Vec3d(-0.02, 0.0, 0.0));

	// And it can be further rotated by -Pi/4 around (0, 0.3, 0) (with the
  // rotation along the z axis) with:
	auto ax0 = gp_Ax1(Pnt3d(0.0, 0.3, 0.0), gp::DZ());
	GMesh_Lib::Rotate({ {0, p5} }, ax0, -PI / 4);

	// Point 3 can be duplicated and translated by 0.05 along the y axis by using
  // the `copy()' function, which takes a vector of (dim, tag) pairs as input,
  // and returns another vector of (dim, tag) pairs:
	std::vector<std::pair<Standard_Integer, Standard_Integer>> ov;
	GMesh_Lib::Copy({ {0, p3} }, ov);
	GMesh_Lib::Translate(ov, Vec3d(0.0, 0.05, 0.0));

	// The new point tag is available in ov[0].second, and can be used to create
  // new lines:
	auto p6 = ov.at(0).second;
	auto l7 = GMesh_Lib::AddLine(p3, ov.at(0).second, 7);
	auto l8 = GMesh_Lib::AddLine(ov.at(0).second, p5, 8);
	auto w10 = GMesh_Lib::AddWire({ l5, -l8, -l7, l3 }, 10);
	auto pl11 = GMesh_Lib::AddPlane({ w10 }, 11);

	// In the same way, we can translate copies of the two surfaces 1 and 11 to
  // the right with the following command:
	GMesh_Lib::Copy({ {2, pl1}, {2, pl11} }, ov);
	GMesh_Lib::Translate(ov, Vec3d(0.12, 0.0, 0.0));

	std::cout << " New surfaces: " << ov[0].second << ", " << ov[1].second << std::endl;

	// Volumes are the fourth type of elementary entities in Gmsh. In the same way
  // one defines curve loops to build surfaces, one has to define surface loops
  // (i.e. `shells') to build volumes. The following volume does not have holes
  // and thus consists of a single surface loop:
	auto p100 = GMesh_Lib::AddPoint(Pnt3d(0.0, 0.3, 0.12), lc, 100);
	auto p101 = GMesh_Lib::AddPoint(Pnt3d(0.1, 0.3, 0.12), lc, 101);
	auto p102 = GMesh_Lib::AddPoint(Pnt3d(0.1, 0.35, 0.12), lc, 102);

	// We would like to retrieve the coordinates of point 5 to create point 103,
  // so we synchronize the model, and use `getValue()'
	GMesh_Lib::SynchronizeModel();

	std::vector<Standard_Real> xyz;
	GMesh_Lib::GetValue(0, p5, {}, xyz);
	auto p103 = GMesh_Lib::AddPoint(Pnt3d(xyz.at(0), xyz.at(1), 0.12), lc, 103);

	auto l110 = GMesh_Lib::AddLine(p4, p100, 110);
	auto l111 = GMesh_Lib::AddLine(p3, p101, 111);
	auto l112 = GMesh_Lib::AddLine(p6, p102, 112);
	auto l113 = GMesh_Lib::AddLine(p5, p103, 113);
	auto l114 = GMesh_Lib::AddLine(p103, p100, 114);
	auto l115 = GMesh_Lib::AddLine(p100, p101, 115);
	auto l116 = GMesh_Lib::AddLine(p101, p102, 116);
	auto l117 = GMesh_Lib::AddLine(p102, p103, 117);

	auto w118 = GMesh_Lib::AddWire({ l115, -l111, l3, l110 }, 118);
	auto pl119 = GMesh_Lib::AddPlane({ w118 }, 119);
	auto w120 = GMesh_Lib::AddWire({ l111, l116, -l112, -l7 }, 120);
	auto pl121 = GMesh_Lib::AddPlane({ w120 }, 121);
	auto w122 = GMesh_Lib::AddWire({ l112, l117, -l113, -l8 }, 122);
	auto pl123 = GMesh_Lib::AddPlane({ w122 }, 123);
	auto w124 = GMesh_Lib::AddWire({ l114, -l110, l5, l113 }, 124);
	auto pl125 = GMesh_Lib::AddPlane({ w124 }, 125);
	auto w126 = GMesh_Lib::AddWire({ l115, l116, l117, l114 }, 126);
	auto pl127 = GMesh_Lib::AddPlane({ w126 }, 127);

	auto sh128 = GMesh_Lib::AddShell({ pl127, pl119, pl121, pl123, pl125, pl11 }, 128);
	auto vol129 = GMesh_Lib::AddVolume({ sh128 }, 129);

	// When a volume can be extruded from a surface, it is usually easier to use
  // the `extrude()' function directly instead of creating all the points,
  // curves and surfaces by hand. For example, the following command extrudes
  // the surface 11 along the z axis and automatically creates a new volume (as
  // well as all the needed points, curves and surfaces). As expected, the
  // function takes a vector of (dim, tag) pairs as input as well as the
  // translation vector, and returns a vector of (dim, tag) pairs as output:
	std::vector<std::pair<Standard_Integer, Standard_Integer>> ov2;
	GMesh_Lib::Extrude({ ov.at(1) }, Vec3d(0.0, 0.0, 0.12), ov2);

	// Mesh sizes associated to geometrical points can be set by passing a vector
  // of (dim, tag) pairs for the corresponding points:
	GMesh_Lib::SetSize({ {0, p103}, {0, 105}, {0, 109}, {0, p102}, {0, 28}, {0, 24}, {0, p6}, {0,p5} }, lc * 3);

	// We finish by synchronizing the data from the built-in CAD kernel with the
  // Gmsh model:
	GMesh_Lib::SynchronizeModel();


	GMesh_Lib::Generate(3);

	GMesh_Lib::WriteMesh("t2.msh");

	GMesh_Lib::Finalize();

	return 0;
}