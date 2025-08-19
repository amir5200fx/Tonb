#include <PtdModel_BladeRadialSections.hxx>

#include <PtdModel_RadialSection.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeRadialSections)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theOrigin_;
	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeRadialSections)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theOrigin_;
	ar & theSections_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_BladeRadialSections);