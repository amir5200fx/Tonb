#include <PtdModel_Shape_PropEntity.hxx>

tnbLib::ptdModel::Shape_PropEntity::Shape_PropEntity
(
	const std::shared_ptr<Cad_Shape>& theShape
)
	: PtdModel_Shape(theShape)
{
	// empty body
}

tnbLib::ptdModel::Shape_PropEntity::Shape_PropEntity
(
	std::shared_ptr<Cad_Shape>&& theShape
)
	: PtdModel_Shape(std::move(theShape))
{
	// empty body
}

tnbLib::ptdModel::Shape_PropEntity::Shape_PropEntity
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<Cad_Shape>& theShape
)
	: PtdModel_Shape(theShape)
{
	// empty body
}

tnbLib::ptdModel::Shape_PropEntity::Shape_PropEntity
(
	const Standard_Integer theIndex,
	const word& theName,
	std::shared_ptr<Cad_Shape>&& theShape
)
	: PtdModel_Shape(std::move(theShape))
{
	// empty body
}