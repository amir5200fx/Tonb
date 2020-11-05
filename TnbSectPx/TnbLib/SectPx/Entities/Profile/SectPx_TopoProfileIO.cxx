#include <SectPx_TopoProfile.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_KnotVector.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_TopoProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode0_;
	ar & theNode1_;
	ar & theKnotAlg_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_TopoProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode0_;
	ar & theNode1_;
	ar & theKnotAlg_;
}