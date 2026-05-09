#include <PtdModel_PropShape.hxx>

#include <PtdModel_Shape_PropBlades.hxx>
#include <PtdModel_Shape_PropHub.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_PropShape)
{
	ar & boost::serialization::base_object<PtdModel_Shape>(*this);

	ar & theBlades_;
	ar & theHub_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_PropShape)
{
	ar & boost::serialization::base_object<PtdModel_Shape>(*this);

	ar & theBlades_;
	ar & theHub_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_PropShape);