#include <PtdModel_Shape.hxx>

tnbLib::PtdModel_Shape::PtdModel_Shape
(
	const std::shared_ptr<Cad_Shape>& theShape
)
	: theShape_(theShape)
{
	//- empty body
}

tnbLib::PtdModel_Shape::PtdModel_Shape
(
	std::shared_ptr<Cad_Shape>&& theShape
)
	: theShape_(std::move(theShape))
{
	//- empty body
}

tnbLib::PtdModel_Shape::PtdModel_Shape
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<Cad_Shape>& theShape
)
	: PtdModel_Entity(theIndex, theName)
	, theShape_(theShape)
{
	//- empty body
}

tnbLib::PtdModel_Shape::PtdModel_Shape
(
	const Standard_Integer theIndex,
	const word& theName,
	std::shared_ptr<Cad_Shape>&& theShape
)
	: PtdModel_Entity(theIndex, theName)
	, theShape_(std::move(theShape))
{
	//- empty body
}

void tnbLib::PtdModel_Shape::SetShape(const std::shared_ptr<Cad_Shape>& theShape)
{
	theShape_ = theShape;
}

void tnbLib::PtdModel_Shape::SetShape(std::shared_ptr<Cad_Shape>&& theShape)
{
	theShape_ = std::move(theShape);
}