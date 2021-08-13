#include <PtdModel_Section.hxx>

#include <PtdModel_SectionCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_Section)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_Section)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_Section);