#include <Marine_ShapeIO.hxx>

#include <Cad_Shape.hxx>

const std::string tnbLib::marineLib::io::Shape::extension = ".hsshape";

std::shared_ptr<tnbLib::Entity3d_Box>
tnbLib::marineLib::io::Shape::BoundingBox() const
{
	return theShape_->BoundingBox();
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::Shape)
{
	ar & theShape_;

	ar & theTol_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::Shape)
{
	ar & theShape_;

	ar & theTol_;
}