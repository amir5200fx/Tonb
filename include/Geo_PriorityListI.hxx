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
		ar & boost::serialization::base_object<Geo_PriorityListBase>(*this);

		ar & theData_;
		ar & LengthValue;
	}
}