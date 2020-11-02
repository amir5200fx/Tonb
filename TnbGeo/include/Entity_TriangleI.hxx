#pragma once
namespace tnbLib
{
	template<class PointRef>
	void Entity_Triangle<PointRef>::save(TNB_oARCH_TYPE & ar, const unsigned int version) const
	{
		ar << P0();
		ar << P1();
		ar << P2();
	}

	template<class PointRef>
	void Entity_Triangle<PointRef>::load(TNB_iARCH_TYPE & ar, const unsigned int version)
	{

	}
}