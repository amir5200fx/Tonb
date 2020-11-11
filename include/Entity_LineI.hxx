#pragma once
namespace tnbLib
{

	template<class Point, class Direct>
	template<class Archive>
	void tnbLib::Entity_Line<Point, Direct>::serialize
	(
		Archive & ar, 
		const unsigned int version
	)
	{
		ar & P();
		ar & Dir();
	}
}