#include <Marine_SectionsIO.hxx>

#include <Pln_Edge.hxx>
#include <Marine_ShapeIO.hxx>

const std::string tnbLib::marineLib::io::Sections::extention = ".hsssects";

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::Sections::Section)
{
	ar & theEdges_;
	ar & theX_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::Sections::Section)
{
	ar & theEdges_;
	ar & theX_;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::Sections)
{
	ar & theShape_;
	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::Sections)
{
	ar & theShape_;
	ar & theSections_;
}