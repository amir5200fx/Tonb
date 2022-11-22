#include <Discret3d_Surface_SizeFunction.hxx>

#include <Discret_Curve_Samples.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Discret3d_Surface_SizeFunction)
{
	ar & boost::serialization::base_object<Discret3d_Surface_Function>(*this);
	ar & theSamples_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Discret3d_Surface_SizeFunction)
{
	ar & boost::serialization::base_object<Discret3d_Surface_Function>(*this);
	ar & theSamples_;
}