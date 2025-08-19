#include <Marine_AnalysisSectionsReportIO.hxx>

#include <Marine_AnalysisSectionsIO.hxx>

const std::string tnbLib::marineLib::io::AnalysisSectionsReport::extension = ".hsasectsr";

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSectionsReport)
{
	ar & theAnalysis_;
	ar & validSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::AnalysisSectionsReport)
{
	ar & theAnalysis_;
	ar & validSections_;
}