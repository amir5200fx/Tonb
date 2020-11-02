#pragma once
namespace tnbLib
{

	template<class Point, class Direct>
	void Entity_Line<Point, Direct>::save(TNB_oARCH_TYPE & ar, const unsigned int version) const
	{
		ar << P();
		ar << Dir();
	}

	template<class Point, class Direct>
	void Entity_Line<Point, Direct>::load(TNB_iARCH_TYPE & ar, const unsigned int version)
	{
		ar >> P();
		ar >> Dir();
	}
}