#pragma once
namespace tnbLib
{

	inline Vec3d operator*(const Standard_Real h, const Dir3d& theDir)
	{
		Vec3d v(theDir.X() * h, theDir.Y() * h, theDir.Z() * h);
		return std::move(v);
	}

	inline Vec3d operator*(const Dir3d& theDir, const Standard_Real h)
	{
		auto v = h * theDir;
		return std::move(v);
	}
}