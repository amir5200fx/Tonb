#pragma once
namespace tnbLib
{
	inline Pnt2d 
		sectPxLib::Datum_Compnt::Coord() const
	{
		return Pnt2d(xCoord(), yCoord());
	}
}