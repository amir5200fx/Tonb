#include <Aft2d_SolutionDataAnIso.hxx>

#include <Aft2d_MetricPrcsrAnIso.hxx>
#include <Entity2d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_SolutionDataAnIso)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theMetric_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_SolutionDataAnIso)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theMetric_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SolutionDataAnIso);