#include <Voyage_Weather.hxx>

#include <Voyage_Wave.hxx>
#include <Voyage_Wind.hxx>
#include <Voyage_Current.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Voyage_Weather)
{
	ar& theWave_;
	ar& theWind_;
	ar& theCurrent_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Voyage_Weather)
{
	ar& theWave_;
	ar& theWind_;
	ar& theCurrent_;
}