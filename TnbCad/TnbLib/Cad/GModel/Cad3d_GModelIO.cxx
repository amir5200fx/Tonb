#include <Cad3d_GModel.hxx>

#include <GModel_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad3d_GModel)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theSurfaces_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad3d_GModel)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theSurfaces_;
}