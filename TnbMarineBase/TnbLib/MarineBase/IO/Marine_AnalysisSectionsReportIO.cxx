#include <Marine_AnalysisSectionsReportIO.hxx>

#include <Marine_AnalysisSectionsIO.hxx>

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