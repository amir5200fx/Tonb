#include <SectPx_OneParCPtsMap.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_OneParCPtsMap)
{
	ar & boost::serialization::base_object<SectPx_CPtsMap>(*this);
	ar & thePar_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_OneParCPtsMap)
{
	ar & boost::serialization::base_object<SectPx_CPtsMap>(*this);
	ar & thePar_;
}