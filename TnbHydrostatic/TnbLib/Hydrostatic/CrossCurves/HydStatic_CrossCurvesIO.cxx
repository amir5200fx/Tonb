#include <HydStatic_CrossCurves.hxx>

#include <Geo_Serialization.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Body.hxx>
#include <Marine_Graph.hxx>
#include <HydStatic_HeelSpacing.hxx>
#include <HydStatic_CrsCurveQ.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_CrossCurves)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theAx_;
	ar & theNbWaters_;
	ar & theDomain_;
	Marine_Body::Save(ar, theBody_);
	ar & theHeels_;
	ar & theCrossCurves_;
	ar & theVolCoeff_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_CrossCurves)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theAx_;
	ar & theNbWaters_;
	ar & theDomain_;
	Marine_Body::Load(ar, theBody_);
	ar & theHeels_;
	ar & theCrossCurves_;
	ar & theVolCoeff_;
}