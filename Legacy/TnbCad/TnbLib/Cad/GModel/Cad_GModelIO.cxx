#include <Cad_GModel.hxx>

#include <GModel_Surface.hxx>
#include <Cad_Shape.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_GModel)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theSurfaces_;
	ar & theShape_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_GModel)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theSurfaces_;
	ar & theShape_;

	if (Shape())
	{
		SetFaces();
	}
}