#pragma once
inline tnbLib::Pnt2d 
tnbLib::sectPxLib::Pnt_Compnt::Coord() const
{
	auto pt = Pnt2d(xCoord(), yCoord());
	return std::move(pt);
}