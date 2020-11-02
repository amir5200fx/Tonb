#pragma once
namespace tnbLib
{

	template<class Point>
	void Entity_Segment<Point>::save(TNB_oARCH_TYPE & ar, const unsigned int version) const
	{
		ar << P0();
		ar << P1();
	}

	template<class Point>
	void Entity_Segment<Point>::load(TNB_iARCH_TYPE & ar, const unsigned int version)
	{
		ar >> P0Ref();
		ar >> P1Ref();
	}
}