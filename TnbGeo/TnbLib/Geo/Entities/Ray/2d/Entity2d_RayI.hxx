#pragma once
namespace tnbLib
{

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Entity2d_Ray&);
	std::istream& operator>>(std::istream& is, Entity2d_Ray&);

	Ostream& operator<<(Ostream& os, const Entity2d_Ray&);
	Istream& operator>>(Istream& is, Entity2d_Ray&);
}