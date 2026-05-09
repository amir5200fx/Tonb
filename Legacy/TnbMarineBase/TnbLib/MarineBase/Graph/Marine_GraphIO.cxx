#include <Marine_Graph.hxx>

#include <Marine_GraphTitle.hxx>
#include <Marine_GraphAxis_X.hxx>
#include <Marine_GraphAxis_Y.hxx>
#include <Marine_GraphCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_Graph)
{
	ar & boost::serialization::base_object<Marine_GraphEntity>(*this);
	ar & theTitle_;
	ar & theX_;
	ar & theY_;
	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_Graph)
{
	ar & boost::serialization::base_object<Marine_GraphEntity>(*this);
	ar & theTitle_;
	ar & theX_;
	ar & theY_;
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_Graph);