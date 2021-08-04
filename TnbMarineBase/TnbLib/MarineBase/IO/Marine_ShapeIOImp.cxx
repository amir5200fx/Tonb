#include <Marine_ShapeIO.hxx>

#include <Cad_Shape.hxx>
#include <Entity3d_Box.hxx>

#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::Shape)
{
	ar & theShape_;
	ar & theBoundingBox_;

	ar & theAx_;
	ar & theTol_;
	ar & theType_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::Shape)
{
	ar & theShape_;
	ar & theBoundingBox_;

	ar & theAx_;
	ar & theTol_;
	ar & theType_;
}