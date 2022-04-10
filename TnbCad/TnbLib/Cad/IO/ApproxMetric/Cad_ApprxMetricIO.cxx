#include <Cad_ApprxMetricIO.hxx>

#include <Cad_Shape.hxx>
#include <GModel_Surface.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>

const std::string tnbLib::Cad_ApprxMetricIO::extension = ".apprxMetric";

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_ApprxMetricIO)
{
	ar & theModel_;
	ar & theApprox_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_ApprxMetricIO)
{
	ar & theModel_;
	ar & theApprox_;
}