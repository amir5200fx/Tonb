#include <Cad_tEdgeMakerInfo_Relative.hxx>

#include <Entity3d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_tEdgeMakerInfo_Relative)
{
	ar & boost::serialization::base_object<Cad_tEdgeMakerInfo>(*this);

	ar & theDomain_;
	ar & theTolerance_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_tEdgeMakerInfo_Relative)
{
	ar & boost::serialization::base_object<Cad_tEdgeMakerInfo>(*this);

	ar & theDomain_;
	ar & theTolerance_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad_tEdgeMakerInfo_Relative);