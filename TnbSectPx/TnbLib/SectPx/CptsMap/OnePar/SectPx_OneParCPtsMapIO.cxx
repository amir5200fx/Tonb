#include <SectPx_OneParCPtsMap.hxx>

#include <SectPx_Par.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_OneParCPtsMap)
{
	ar & boost::serialization::base_object<SectPx_CPtsMap>(*this);
	ar & thePar_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_OneParCPtsMap)
{
	ar & boost::serialization::base_object<SectPx_CPtsMap>(*this);
	ar & thePar_;
}