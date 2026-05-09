#include <SectPx_TopoProfile.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_KnotVector.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_TopoProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode0_;
	ar & theNode1_;
	ar & theKnotAlg_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_TopoProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode0_;
	ar & theNode1_;
	ar & theKnotAlg_;
}