#include <PtdModel_Shape_PropBladeChild.hxx>

tnbLib::ptdModel::Shape_PropBladeChild::Shape_PropBladeChild
(
	const std::shared_ptr<Cad_Shape>& theShape
)
	: Shape_PropBlade(theShape)
{
	//- empty body
}

tnbLib::ptdModel::Shape_PropBladeChild::Shape_PropBladeChild
(
	std::shared_ptr<Cad_Shape>&& theShape
)
	: Shape_PropBlade(std::move(theShape))
{
	//- empty body
}

tnbLib::ptdModel::Shape_PropBladeChild::Shape_PropBladeChild
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<Cad_Shape>& theShape
)
	: Shape_PropBlade(theIndex, theName, theShape)
{
	//- empty body
}

tnbLib::ptdModel::Shape_PropBladeChild::Shape_PropBladeChild
(
	const Standard_Integer theIndex,
	const word& theName,
	std::shared_ptr<Cad_Shape>&& theShape
)
	: Shape_PropBlade(theIndex, theName, std::move(theShape))
{
	//- empty body
}