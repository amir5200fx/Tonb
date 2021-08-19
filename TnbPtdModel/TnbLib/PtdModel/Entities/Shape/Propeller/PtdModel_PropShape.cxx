#include <PtdModel_PropShape.hxx>

tnbLib::PtdModel_PropShape::PtdModel_PropShape
(
	const std::shared_ptr<ptdModel::Shape_PropHub>& theHub,
	const std::shared_ptr<ptdModel::Shape_PropBlades>& theBlades
)
	: theHub_(theHub)
	, theBlades_(theBlades)
{
	// empty body
}

tnbLib::PtdModel_PropShape::PtdModel_PropShape
(
	std::shared_ptr<ptdModel::Shape_PropHub>&& theHub,
	std::shared_ptr<ptdModel::Shape_PropBlades>&& theBlades
)
	: theHub_(std::move(theHub))
	, theBlades_(std::move(theBlades))
{
	// empty body
}

void tnbLib::PtdModel_PropShape::SetBlades(const std::shared_ptr<ptdModel::Shape_PropBlades>& theShape)
{
	theBlades_ = theShape;
}

void tnbLib::PtdModel_PropShape::SetBlades(std::shared_ptr<ptdModel::Shape_PropBlades>&& theShape)
{
	theBlades_ = std::move(theShape);
}

void tnbLib::PtdModel_PropShape::SetHub(const std::shared_ptr<ptdModel::Shape_PropHub>& theShape)
{
	theHub_ = theShape;
}

void tnbLib::PtdModel_PropShape::SetHub(std::shared_ptr<ptdModel::Shape_PropHub>&& theShape)
{
	theHub_ = std::move(theShape);
}