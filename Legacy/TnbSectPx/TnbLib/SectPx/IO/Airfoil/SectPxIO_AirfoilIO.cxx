#include <SectPxIO_Airfoil.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_ProfileMaker.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPxIO_Airfoil)
{
	ar& theRegistry_;
	ar& theFrame_;
	ar& theTuner_;
	ar& theCamber_;
	ar& theThickness_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPxIO_Airfoil)
{
	ar& theRegistry_;
	ar& theFrame_;
	ar& theTuner_;
	ar& theCamber_;
	ar& theThickness_;
}