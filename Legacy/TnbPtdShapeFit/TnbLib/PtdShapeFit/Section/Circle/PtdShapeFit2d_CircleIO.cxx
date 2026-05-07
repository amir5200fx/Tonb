#include <PtdShapeFit2d_Circle.hxx>

#include <PtdShapeFit_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdShapeFit2d_Circle)
{
	ar& boost::serialization::base_object<PtdShapeFit_Section>(*this);

	ar& theDir_;
	ar& theXo_;
	ar& theYo_;
	ar& theRadius_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdShapeFit2d_Circle)
{
	ar& boost::serialization::base_object<PtdShapeFit_Section>(*this);

	ar& theDir_;
	ar& theXo_;
	ar& theYo_;
	ar& theRadius_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdShapeFit2d_Circle);