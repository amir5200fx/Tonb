#include <Marine_AnalysisSectionsIO.hxx>

#include <Marine_SectionsIO.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections::Section)
{
	ar & theSegments_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections::Section)
{
	ar & theSegments_;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections)
{
	ar & theModel_;
	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections)
{
	ar & theModel_;
	ar & theSections_;
}