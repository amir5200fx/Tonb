#include <SectPx_FieldCloud_Naca4Digit.hxx>

#include <SectPx_Par.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::FieldCloud_Naca4DigitBase)
{
	ar & boost::serialization::base_object<SectPx_FieldCloud>(*this);
	ar & theChord_;
	ar & theMaxCamber_;
	ar & theMaxCamberLoc_;
	ar & theMaxThickness_;
	ar & theNbSegments_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::FieldCloud_Naca4DigitBase)
{
	ar & boost::serialization::base_object<SectPx_FieldCloud>(*this);
	ar & theChord_;
	ar & theMaxCamber_;
	ar & theMaxCamberLoc_;
	ar & theMaxThickness_;
	ar & theNbSegments_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::naca::UpperEdge);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::naca::LowerEdge);