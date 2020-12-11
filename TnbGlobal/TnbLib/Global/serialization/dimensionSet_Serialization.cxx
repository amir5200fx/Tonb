#include <dimensionSet_Serialization.hxx>

#include <dimensionSet.hxx>

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const tnbLib::dimensionSet & d, 
	const unsigned int version
)
{
	for (int i = 0; i < tnbLib::dimensionSet::nDimensions; i++)
	{
		ar << d[i];
	}
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar, 
	tnbLib::dimensionSet & d, 
	const unsigned int version
)
{
	tnbLib::scalar x[tnbLib::dimensionSet::nDimensions];
	for (int i = 0; i < tnbLib::dimensionSet::nDimensions; i++)
	{
		ar >> x[i];
	}
	tnbLib::dimensionSet s(x[0], x[1], x[2], x[3], x[4], x[5], x[6]);
	d = std::move(s);
}