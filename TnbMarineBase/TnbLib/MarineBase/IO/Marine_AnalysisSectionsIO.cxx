#include <Marine_AnalysisSectionsIO.hxx>

#include <Marine_DisctSectionsIO.hxx>

const std::string tnbLib::marineLib::io::AnalysisSections::extention = ".hsasects";

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections::Section)
{
	ar & theSegments_;
	ar & theX_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections::Section)
{
	ar & theSegments_;
	ar & theX_;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections)
{
	ar & theModel_;
	ar & theSections_;
	ar & theMinTol_;
	ar & theMaxTol_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSections)
{
	ar & theModel_;
	ar & theSections_;
	ar & theMinTol_;
	ar & theMaxTol_;
}