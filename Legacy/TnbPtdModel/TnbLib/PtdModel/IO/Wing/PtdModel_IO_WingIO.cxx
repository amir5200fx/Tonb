#include <PtdModel_IO_Wing.hxx>

#include <PtdModel_Face.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ptdModel::io::Wing)
{
	ar & theUpper_;
	ar & theLower_;

	ar & theSystem_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ptdModel::io::Wing)
{
	ar & theUpper_;
	ar & theLower_;

	ar & theSystem_;
}