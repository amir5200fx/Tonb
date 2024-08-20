#include <GMesh_Lib.hxx>

#include <Geo3d_SizeFunction.hxx>
#include <Entity3d_Triangulation.hxx>

#include <TopoDS_Shape.hxx>

#include <gmsh.h>

void tnbLib::GMesh_Lib::AddTriangle
(
	const Entity_Triangle<const Pnt3d&>& theTriangle, 
	Standard_Real(*theSizeFun)(const Pnt3d&),
	Standard_Integer& theNbNodes, 
	Standard_Integer& theNbEdges,
	Standard_Integer& theNbElements,
	const Standard_Boolean theSense
)
{
	const auto& pt0 = theTriangle.P0();
	const auto& pt1 = theTriangle.P1();
	const auto& pt2 = theTriangle.P2();

	const auto h0 = theSizeFun(pt0);
	const auto h1 = theSizeFun(pt1);
	const auto h2 = theSizeFun(pt2);

	const auto p0 = AddPoint(pt0, h0, ++theNbNodes);
	const auto p1 = AddPoint(pt1, h1, ++theNbNodes);
	const auto p2 = AddPoint(pt2, h2, ++theNbNodes);

	Standard_Integer l0, l1, l2;
	if (theSense)
	{
		l0 = AddLine(p0, p1, ++theNbEdges);
		l1 = AddLine(p1, p2, ++theNbEdges);
		l2 = AddLine(p2, p0, ++theNbEdges);
	}
	else
	{
		l0 = AddLine(p0, p2, ++theNbEdges);
		l1 = AddLine(p2, p1, ++theNbEdges);
		l2 = AddLine(p1, p0, ++theNbEdges);
	}

	auto w = AddWire({ l0,l1,l2 }, -1);
	AddPlane({ w }, ++theNbElements);
}

void tnbLib::GMesh_Lib::AddSurface
(
	const Entity3d_Triangulation& theSurface,
	Standard_Real(*theSizeFun)(const Pnt3d&),
	Standard_Integer& theNbNodes,
	Standard_Integer& theNbEdges,
	Standard_Integer& theNbElements,
	const Standard_Boolean theSense
)
{
	const auto& pnts = theSurface.Points();
	const auto& ids = theSurface.Connectivity();

	for (const auto& i : ids)
	{
		auto v0 = Index_Of(i.Value(0));
		auto v1 = Index_Of(i.Value(1));
		auto v2 = Index_Of(i.Value(2));
		Entity_Triangle<const Pnt3d&> t(pnts.at(v0), pnts.at(v1), pnts.at(v2));
		AddTriangle(t, theSizeFun, theNbNodes, theNbEdges, theNbElements, theSense);

		SynchronizeModel();
	}
}

void tnbLib::GMesh_Lib::Initialize()
{
	gmsh::initialize();
}

void tnbLib::GMesh_Lib::AddModel(const word& theName)
{
	gmsh::model::add(theName);
}

Standard_Integer 
tnbLib::GMesh_Lib::AddPoint
(
	const Pnt3d& theCoord,
	const Standard_Real theSize,
	const Standard_Integer theTag
)
{
	auto [x, y, z] = theCoord.Components();
	return gmsh::model::geo::addPoint(x, y, z, theSize, theTag);
}

Standard_Integer 
tnbLib::GMesh_Lib::AddLine
(
	const Standard_Integer theP0, 
	const Standard_Integer theP1,
	const Standard_Integer theTag
)
{
	return gmsh::model::geo::addLine(theP0, theP1, theTag);
}

Standard_Integer 
tnbLib::GMesh_Lib::AddWire
(
	const std::vector<Standard_Integer>& theLines,
	const Standard_Integer theTag,
	const Standard_Boolean theSense
)
{
	return gmsh::model::geo::addCurveLoop(theLines, theTag, theSense);
}

Standard_Integer 
tnbLib::GMesh_Lib::AddPlane
(
	const std::vector<Standard_Integer>& theWires,
	const Standard_Integer theTag
)
{
	return gmsh::model::geo::addPlaneSurface(theWires, theTag);
}

Standard_Integer 
tnbLib::GMesh_Lib::AddShell
(
	const std::vector<Standard_Integer>& thePlanes,
	const Standard_Integer theTag
)
{
	return gmsh::model::geo::addSurfaceLoop(thePlanes, theTag);
}

Standard_Integer 
tnbLib::GMesh_Lib::AddVolume
(
	const std::vector<Standard_Integer>& theTags,
	const Standard_Integer theTag
)
{
	return gmsh::model::geo::addVolume(theTags, theTag);
}

void tnbLib::GMesh_Lib::SynchronizeModel()
{
	gmsh::model::geo::synchronize();
}

void tnbLib::GMesh_Lib::SynchronizeShape()
{
	gmsh::model::occ::synchronize();
}

Standard_Integer 
tnbLib::GMesh_Lib::AddPhysicalGroup
(
	const Standard_Integer theDim,
	const std::vector<Standard_Integer>& theTags,
	const Standard_Integer theTag,
	const word& theName
)
{
	return gmsh::model::addPhysicalGroup(theDim, theTags, theTag, theName);
}

void tnbLib::GMesh_Lib::Translate
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags,
	const Vec3d& theV
)
{
	auto dx = theV.X();
	auto dy = theV.Y();
	auto dz = theV.Z();
	gmsh::model::geo::translate(theDimTags, dx, dy, dz);
}

void tnbLib::GMesh_Lib::Rotate
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags,
	const gp_Ax1& theAx,
	const Standard_Real theAngle
)
{
	const auto& pt = theAx.Location();
	const auto& dir = theAx.Direction();

	auto x = pt.X();
	auto y = pt.Y();
	auto z = pt.Z();
	auto dx = dir.X();
	auto dy = dir.Y();
	auto dz = dir.Z();
	gmsh::model::geo::rotate(theDimTags, x, y, z, dx, dy, dz, theAngle);
}

void tnbLib::GMesh_Lib::Copy
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags,
	std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
)
{
	gmsh::model::geo::copy(theDimTags, theOutDimTags);
}

void tnbLib::GMesh_Lib::GetValue
(
	const Standard_Integer theDim, 
	const Standard_Integer theTag, 
	const std::vector<Standard_Real>& theParametricCoord,
	std::vector<Standard_Real>& theCoord
)
{
	gmsh::model::getValue(theDim, theTag, theParametricCoord, theCoord);
}

void tnbLib::GMesh_Lib::Extrude
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags, 
	const Vec3d& theVec,
	std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags,
	const std::vector<Standard_Integer>& theNumElements,
	const std::vector<Standard_Real>& theHeights,
	const Standard_Boolean recombine
)
{
	auto dx = theVec.X();
	auto dy = theVec.Y();
	auto dz = theVec.Z();
	gmsh::model::geo::extrude
	(
		theDimTags, dx, dy, dz, 
		theOutDimTags,
		theNumElements,
		theHeights, 
		recombine
	);
}

void tnbLib::GMesh_Lib::ImportShape
(
	const TopoDS_Shape& theShape,
	std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
)
{
	const void* shape = static_cast<const void*>(&theShape);
	gmsh::model::occ::importShapesNativePointer(shape, theOutDimTags);
}

void tnbLib::GMesh_Lib::ImportSTEP
(
	const std::string& name,
	std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
)
{
	gmsh::model::occ::importShapes(name, theOutDimTags, true, "step");
}

void tnbLib::GMesh_Lib::ImportIGES
(
	const std::string& name,
	std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
)
{
	gmsh::model::occ::importShapes(name, theOutDimTags, true, "iges");
}

void tnbLib::GMesh_Lib::ImportSTL(const std::string& name,
	std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags)
{
	gmsh::model::occ::importShapes(name, theOutDimTags, true, "stl");
}

void tnbLib::GMesh_Lib::SetSizeMap(const Geo3d_SizeFunction& theSizeMap)
{
	auto meshSize = [&theSizeMap](int /*dim*/, int /*tag*/, double x, double y, double z,
		double /*lc*/
		)
	{
		Pnt3d pt(x, y, z);
		return theSizeMap.Value(pt);
	};
	gmsh::model::mesh::setSizeCallback(meshSize);
}

void tnbLib::GMesh_Lib::SetSize
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags, 
	const Standard_Real theSize
)
{
	gmsh::model::geo::mesh::setSize(theDimTags, theSize);
}

void tnbLib::GMesh_Lib::Generate(const Standard_Integer theDim)
{
	gmsh::model::mesh::generate(theDim);
}

void tnbLib::GMesh_Lib::WriteMesh(const std::string& theName)
{
	gmsh::write(theName);
}

void tnbLib::GMesh_Lib::Finalize()
{
	gmsh::finalize();
}