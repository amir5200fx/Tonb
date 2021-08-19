#include <PtdModel_SolidMaker_PropBlade.hxx>

#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_PropBlade.hxx>
#include <PtdModel_Face.hxx>
#include <Cad_Shape.hxx>
#include <OpenCascade_Serialization.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>

//TNB_SAVE_IMPLEMENTATION(tnbLib::ptdModel::SolidMaker_PropBlade::Faces)
//{
//	ar & Leading;
//	ar & Root;
//	ar & Tip;
//	ar & Trailing;
//}
//
//TNB_LOAD_IMPLEMENTATION(tnbLib::ptdModel::SolidMaker_PropBlade::Faces)
//{
//	ar & Leading;
//	ar & Root;
//	ar & Tip;
//	ar & Trailing;
//}

TNB_SAVE_IMPLEMENTATION(tnbLib::ptdModel::SolidMaker_PropBlade)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theBlade_;
	ar & theShape_;

	ar & theTolerance_;

	ar & hasLeadingPatch_;
	ar & hasTrailingPatch_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ptdModel::SolidMaker_PropBlade)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theBlade_;
	ar & theShape_;

	ar & theTolerance_;

	ar & hasLeadingPatch_;
	ar & hasTrailingPatch_;
}