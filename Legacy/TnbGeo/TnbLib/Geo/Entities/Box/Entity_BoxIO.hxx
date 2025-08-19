#pragma once
namespace tnbLib
{

	template<class Point>
	template<class Archive>
	void Entity_Box<Point>::serialize(Archive & ar, const unsigned int version)
	{
		ar & P0();
		ar & P1();
	}

	template<class Point>
	std::ostream& operator<<(std::ostream& os, const Entity_Box<Point>& b)
	{
		os
			<< " P0 = ("
			<< b.P0()
			<< "),  P1 = ("
			<< b.P1()
			<< ")";
		return os;
	}

	template<class Point>
	Ostream & operator<<(Ostream & os, const Entity_Box<Point>& b)
	{
		os << " P0 = " << b.P0() << ", P1 = " << b.P1();
		os.check("Ostream & operator<<(Ostream & os, const Entity_Box<Point>& b)");
		return os;
	}
}