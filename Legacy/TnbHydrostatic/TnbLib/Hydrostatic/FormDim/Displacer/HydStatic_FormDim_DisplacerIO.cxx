#include <HydStatic_FormDim_Displacer.hxx>

#include <Marine_Bodies.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::formDim::Displacer::Parameter)
{
	ar & B;
	ar & D;
	ar & Loa;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formDim::Displacer::Parameter)
{
	ar & B;
	ar & D;
	ar & Loa;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::formDim::Displacer)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	Marine_Body::Save(ar, theBody_);
	//ar & theBody_;
	ar & theParameters_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formDim::Displacer)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	std::shared_ptr<Marine_Body> b;
	Marine_Body::Load(ar, b);
	theBody_ = std::dynamic_pointer_cast<marineLib::Body_Displacer>(b);
	//ar & theBody_;
	ar & theParameters_;
}