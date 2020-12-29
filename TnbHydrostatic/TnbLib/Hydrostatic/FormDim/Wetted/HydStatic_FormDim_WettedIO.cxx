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
	//Marine_Body::Save(ar, theBody_);
	//Marine_Wave::Save(ar, theWave_);
	ar & theParameters_;
	ar & theAppMode_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formDim::Wetted)
{
	Info << 0 << endl;
	ar & boost::serialization::base_object<Global_Done>(*this);
	Info << 1 << endl;	
	/*std::shared_ptr<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>> bb;
	ar & bb;
	theBody_ = bb;*/
	ar & theBody_;
	/*std::shared_ptr<Marine_Body> b;
	Marine_Body::Load(ar, b);
	theBody_ = std::dynamic_pointer_cast<marineLib::Body_Wetted>(b);*/
	Info << 2 << endl;
	//Marine_Wave::Load(ar, theWave_);	
	ar & theWave_;
	Info << 3 << endl;
	ar & theParameters_;
	Info << 4 << endl;
	ar & theAppMode_;
}