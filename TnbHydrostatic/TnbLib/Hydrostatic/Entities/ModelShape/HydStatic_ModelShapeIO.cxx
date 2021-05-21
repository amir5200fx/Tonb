#include <HydStatic_ModelShape.hxx>

#include <HydStatic_Shapes.hxx>
#include <Marine_Domain.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_ModelShape)
{
	ar & theHull_;
	ar & theTanks_;
	ar & theSails_;

	ar & theWeight_;

	ar & theDomain_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_ModelShape)
{
	ar & theHull_;
	ar & theTanks_;
	ar & theSails_;

	ar & theWeight_;

	ar & theDomain_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_ModelShape);