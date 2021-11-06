#include <Cad_Shape.hxx>

#include <Entity3d_Box.hxx>
#include <Cad_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::string tnbLib::Cad_Shape::extension = ".shape";

tnbLib::Cad_Shape::Cad_Shape
(
	const TopoDS_Shape & theShape
)
	: theShape_(theShape)
{
	CalcBoundingBox();
}

tnbLib::Cad_Shape::Cad_Shape
(
	const Standard_Integer theIndex,
	const word & theName, 
	const TopoDS_Shape & theShape
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theShape_(theShape)
{
	CalcBoundingBox();
}

tnbLib::Cad_Shape::Cad_Shape
(
	TopoDS_Shape && theShape
)
	: theShape_(std::move(theShape))
{
	CalcBoundingBox();
}

tnbLib::Cad_Shape::Cad_Shape
(
	const Standard_Integer theIndex,
	const word & theName,
	TopoDS_Shape && theShape
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theShape_(std::move(theShape))
{
	CalcBoundingBox();
}

#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>

void tnbLib::Cad_Shape::CalcBoundingBox()
{
	if (Shape().IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "the shape is null" << endl
			<< abort(FatalError);
	}
	Bnd_Box box;
	BRepBndLib::AddOptimal(Shape(), box, Standard_False, Standard_False);

	auto b = Cad_Tools::BoundingBox(box);
	theBoundingBox_ = std::make_shared<Entity3d_Box>(std::move(b));
}