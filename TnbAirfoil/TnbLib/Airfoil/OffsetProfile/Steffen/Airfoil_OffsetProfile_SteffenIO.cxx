#include <Airfoil_OffsetProfile_Steffen.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Airfoil_OffsetProfile_Steffen)
{
	ar & boost::serialization::base_object<Airfoil_OffsetProfile>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Airfoil_OffsetProfile_Steffen)
{
	ar & boost::serialization::base_object<Airfoil_OffsetProfile>(*this);

	Perform();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Airfoil_OffsetProfile_Steffen);