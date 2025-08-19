#include <Marine_HullShapeIO.hxx>

#include <Entity3d_Box.hxx>
#include <Geo_Serialization.hxx>

std::shared_ptr<tnbLib::Entity3d_Box> 
tnbLib::marineLib::io::HullShape::BoundingBox() const
{
	return PreciseBndBox();
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::HullShape)
{
	ar & boost::serialization::base_object<Shape>(*this);

	ar & theAx_;
	ar & theType_;
	ar & theBoundingBox_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::HullShape)
{
	ar & boost::serialization::base_object<Shape>(*this);

	ar & theAx_;
	ar & theType_;
	ar & theBoundingBox_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::io::HullShape);