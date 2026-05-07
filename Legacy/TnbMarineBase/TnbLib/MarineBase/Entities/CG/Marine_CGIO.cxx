#include <Marine_CG.hxx>

#include <Marine_LCG.hxx>
#include <Marine_VCG.hxx>
#include <Marine_TCG.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_CG)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);

	ar & theLCG_;
	ar & theVCG_;
	ar & theTCG_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_CG)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);

	ar & theLCG_;
	ar & theVCG_;
	ar & theTCG_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_CG);