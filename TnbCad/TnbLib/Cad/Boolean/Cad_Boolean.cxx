#include <Cad_Boolean.hxx>

#include <opencascade/BRepAlgoAPI_Fuse.hxx>
#include <opencascade/BRepAlgoAPI_Cut.hxx>
#include <opencascade/BRepAlgoAPI_Common.hxx>
#include <opencascade/TopoDS_Shape.hxx>

TopoDS_Shape 
tnbLib::Cad_Boolean::Union
(
	const TopoDS_Shape & theShape0, 
	const TopoDS_Shape & theShape1
)
{
	TopoDS_Shape Sum = BRepAlgoAPI_Fuse(theShape0, theShape1);

	return std::move(Sum);
}

TopoDS_Shape 
tnbLib::Cad_Boolean::Subtract
(
	const TopoDS_Shape & theTarget, 
	const TopoDS_Shape & theShape
)
{
	TopoDS_Shape Sum = BRepAlgoAPI_Cut(theTarget, theShape);

	return std::move(Sum);
}

TopoDS_Shape 
tnbLib::Cad_Boolean::Intersection
(
	const TopoDS_Shape & theShape0, 
	const TopoDS_Shape & theShape1
)
{
	TopoDS_Shape Sum = BRepAlgoAPI_Common(theShape0, theShape1);

	return std::move(Sum);
}