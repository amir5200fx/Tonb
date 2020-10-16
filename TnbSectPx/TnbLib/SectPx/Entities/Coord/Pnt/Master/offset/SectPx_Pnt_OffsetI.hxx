#pragma once
namespace tnbLib
{
	inline Pnt2d
		sectPxLib::Pnt_Offset::Coord() const
	{
		auto pt = Pnt2d(X(), Y());
		return std::move(pt);
	}
}
