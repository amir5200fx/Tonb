#include <GModel_Wire.hxx>

#include <GModel_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_Wire)
{
	ar & boost::serialization::base_object<GModel_Entity>(*this);

	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_Wire)
{
	ar & boost::serialization::base_object<GModel_Entity>(*this);

	ar & theEdges_;
}