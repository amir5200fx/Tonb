#include <PtdModel_Shape_PropBladeParent.hxx>

#include <Geo_Serialization.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <PtdModel_Face.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ptdModel::Shape_PropBladeParent)
{
	ar & boost::serialization::base_object<Shape_PropBlade>(*this);

	ar & theInfo_;
	ar & theFaces_;
	ar & theAx_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ptdModel::Shape_PropBladeParent)
{
	ar & boost::serialization::base_object<Shape_PropBlade>(*this);

	ar & theInfo_;
	ar & theFaces_;
	ar & theAx_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ptdModel::Shape_PropBladeParent);