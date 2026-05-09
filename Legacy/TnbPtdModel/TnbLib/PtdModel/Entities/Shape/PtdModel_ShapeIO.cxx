#include <PtdModel_Shape.hxx>

#include <Cad_Shape.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_Shape)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theShape_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_Shape)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theShape_;
}