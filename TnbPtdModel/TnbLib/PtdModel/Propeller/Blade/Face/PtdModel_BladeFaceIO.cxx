#include <PtdModel_BladeFace.hxx>

#include <OpenCascade_Serialization.hxx>

#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeFace)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theSurface_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeFace)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theSurface_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_BladeFace);