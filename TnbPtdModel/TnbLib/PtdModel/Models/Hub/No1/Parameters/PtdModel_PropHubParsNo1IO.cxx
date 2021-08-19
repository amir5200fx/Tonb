#include <PtdModel_PropHubParsNo1.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_PropHubParsNo1)
{
	ar & boost::serialization::base_object<PtdModel_PropHubPars>(*this);

	ar & theOffset_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_PropHubParsNo1)
{
	ar & boost::serialization::base_object<PtdModel_PropHubPars>(*this);

	ar & theOffset_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_PropHubParsNo1);