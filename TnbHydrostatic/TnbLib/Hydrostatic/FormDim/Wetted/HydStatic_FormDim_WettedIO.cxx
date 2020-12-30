#include <HydStatic_FormDim_Wetted.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_Wave.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::formDim::Wetted::Parameter)
{
	ar & Tm;
	ar & App;
	ar & Fpp;
	ar & Mpp;
	ar & Lpp;
	ar & Bwl;
	ar & Lwl;
	ar & Fwl;
	ar & Awl;
	ar & Fuw;
	ar & Auw;
	ar & Los;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formDim::Wetted::Parameter)
{
	ar & Tm;
	ar & App;
	ar & Fpp;
	ar & Mpp;
	ar & Lpp;
	ar & Bwl;
	ar & Lwl;
	ar & Fwl;
	ar & Awl;
	ar & Fuw;
	ar & Auw;
	ar & Los;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::formDim::Wetted)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theBody_;
	ar & theWave_;
	ar & theParameters_;
	ar & theAppMode_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formDim::Wetted)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theBody_;
	ar & theWave_;
	ar & theParameters_;
	ar & theAppMode_;
}