#include <Cad_TModel.hxx>

#include <OpenCascade_Serialization.hxx>
#include <TModel_Shell.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_TModel)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<Cad_TModelManager>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theShape_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_TModel)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<Cad_TModelManager>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theShape_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad_TModel);