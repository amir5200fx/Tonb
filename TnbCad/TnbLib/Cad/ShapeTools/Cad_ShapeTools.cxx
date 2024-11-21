#include <Cad_ShapeTools.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/BRepPrimAPI_MakeBox.hxx>
#include <opencascade/BRepPrimAPI_MakeCylinder.hxx>
#include <opencascade/BRepPrimAPI_MakeSphere.hxx>

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Box
(
	const Pnt3d & theP0, 
	const Pnt3d & theP1
)
{
	auto shape = BRepPrimAPI_MakeBox(theP0, theP1);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Box
(
	const Pnt3d & theP0,
	const Standard_Real dx, 
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	auto shape = BRepPrimAPI_MakeBox(theP0, dx, dy, dz);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Box
(
	const gp_Ax2 & theAx, 
	const Standard_Real dx, 
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	auto shape = BRepPrimAPI_MakeBox(theAx, dx, dy, dz);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Cylinder
(
	const gp_Ax2 & theAx, 
	const Standard_Real theR, 
	const Standard_Real theH
)
{
	auto shape = BRepPrimAPI_MakeCylinder(theAx, theR, theH);
	return std::move(shape);
}

TopoDS_Shape
tnbLib::Cad_ShapeTools::Cylinder
(
	const gp_Ax2 & theAx, 
	const Standard_Real theR,
	const Standard_Real theH,
	const Standard_Real theAngle
)
{
	auto shape = BRepPrimAPI_MakeCylinder(theAx, theR, theH, theAngle);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Sphere
(
	const Pnt3d & theC, 
	const Standard_Real theR
)
{
	auto shape = BRepPrimAPI_MakeSphere(theC, theR);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Sphere
(
	const gp_Ax2 & theAx, 
	const Standard_Real theR
)
{
	auto shape = BRepPrimAPI_MakeSphere(theAx, theR);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Sphere
(
	const gp_Ax2 & theAx,
	const Standard_Real theR, 
	const Standard_Real theAngle1
)
{
	auto shape = BRepPrimAPI_MakeSphere(theAx, theR, theAngle1);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Sphere
(
	const gp_Ax2 & theAx, 
	const Standard_Real theR,
	const Standard_Real theAngle1, 
	const Standard_Real theAngle2
)
{
	auto shape = BRepPrimAPI_MakeSphere(theAx, theR, theAngle1, theAngle2);
	return std::move(shape);
}

TopoDS_Shape 
tnbLib::Cad_ShapeTools::Sphere
(
	const gp_Ax2 & theAx, 
	const Standard_Real theR, 
	const Standard_Real theAngle1, 
	const Standard_Real theAngle2, 
	const Standard_Real theAngle3
)
{
	auto shape = BRepPrimAPI_MakeSphere(theAx, theR, theAngle1, theAngle2, theAngle3);
	return std::move(shape);
}