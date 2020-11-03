#pragma once
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
		ar & theData_;
		ar & LengthValue;
	}
}