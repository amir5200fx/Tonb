#include <SectPx_Edge.hxx>

#include <SectPx_Pnt.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_Edge)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theP0_;
	ar & theP1_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_Edge)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theP0_;
	ar & theP1_;
}