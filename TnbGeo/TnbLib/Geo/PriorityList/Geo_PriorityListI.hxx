#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class T>
	template<class Archive>
	void Geo_PriorityList<T>::serialize
	(
		Archive & ar, 
		const unsigned int version
	)
	{
		Info << " This function is not supposed to be called!" << endl;
		NotImplemented;
	}
}