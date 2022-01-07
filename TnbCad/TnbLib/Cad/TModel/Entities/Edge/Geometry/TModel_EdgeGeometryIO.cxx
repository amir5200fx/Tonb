#include <TModel_EdgeGeometry.hxx>

#include <TModel_ParaCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_EdgeGeometry)
{
	ar & theParaCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_EdgeGeometry)
{
	ar & theParaCurve_;
}