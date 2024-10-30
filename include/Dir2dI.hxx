#pragma once
namespace tnbLib
{

	inline Vec2d operator*(const Standard_Real d, const Dir2d& theDir)
	{
		Vec2d vec(d * theDir.X(), d * theDir.Y());
		return std::move(vec);
	}

	inline Vec2d operator*(const Dir2d& theDir, const Standard_Real d)
	{
		return d * theDir;
	}
}
