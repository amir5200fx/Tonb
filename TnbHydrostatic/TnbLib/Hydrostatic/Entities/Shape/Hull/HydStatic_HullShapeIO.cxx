#include <HydStatic_HullShape.hxx>

#include <Marine_Model_Hull.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_HullShape)
{
	ar & boost::serialization::base_object<HydStatic_Shape>(*this);

	ar & theHull_;
	ar & theCross_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_HullShape)
{
	ar & boost::serialization::base_object<HydStatic_Shape>(*this);

	ar & theHull_;
	ar & theCross_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_HullShape);