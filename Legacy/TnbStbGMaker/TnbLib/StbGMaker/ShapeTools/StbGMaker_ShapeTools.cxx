#include <StbGMaker_ShapeTools.hxx>

#include <Marine_Shapes.hxx>

std::shared_ptr<tnbLib::marineLib::Shape_Sail> 
tnbLib::StbGMaker_ShapeTools::Sail
(
	const TopoDS_Shape & theShape
)
{
	auto shape = std::make_shared<marineLib::Shape_Sail>(theShape);
	return std::move(shape);
}

std::shared_ptr<tnbLib::marineLib::Shape_Hull> 
tnbLib::StbGMaker_ShapeTools::Hull
(
	const TopoDS_Shape & theShape
)
{
	auto shape = std::make_shared<marineLib::Shape_Hull>(theShape);
	return std::move(shape);
}

std::shared_ptr<tnbLib::marineLib::Shape_Tank> 
tnbLib::StbGMaker_ShapeTools::Tank(const TopoDS_Shape & theShape)
{
	auto shape = std::make_shared<marineLib::Shape_Tank>(theShape);
	return std::move(shape);
}