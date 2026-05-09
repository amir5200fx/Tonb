#include <HydStatic_FormCoeff.hxx>

#include <HydStatic_FormDim_Wetted.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::formCoeff::Wetted::Parameter)
{
	ar & Cb;
	ar & Dispv;
	ar & Cm;
	ar & Am;
	ar & Cp;
	ar & Cvp;
	ar & Aw;
	ar & Cwl;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formCoeff::Wetted::Parameter)
{
	ar & Cb;
	ar & Dispv;
	ar & Cm;
	ar & Am;
	ar & Cp;
	ar & Cvp;
	ar & Aw;
	ar & Cwl;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::formCoeff::Wetted)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theWeted_;
	ar & theParameters_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::formCoeff::Wetted)
{
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theWeted_;
	ar & theParameters_;
}