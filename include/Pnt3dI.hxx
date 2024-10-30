#pragma once
inline std::tuple<Standard_Real, Standard_Real, Standard_Real> 
tnbLib::Pnt3d::Components() const
{
	return { X(), Y(), Z() };
}

namespace tnbLib
{

	inline Pnt3d operator+(const Pnt3d& P1, const Pnt3d& P2)
	{
		Pnt3d Temp = P1;
		Temp += P2;
		return Temp;
	}

	inline Pnt3d operator-(const Pnt3d& P1, const Pnt3d& P2)
	{
		Pnt3d Temp = P1;
		Temp -= P2;
		return Temp;
	}

	inline Pnt3d operator+(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp += Scalar;
		return Temp;
	}

	inline Pnt3d operator+(const Standard_Real Scalar, const Pnt3d& P1)
	{
		Pnt3d Temp = P1;
		Temp += Scalar;
		return Temp;
	}

	inline Pnt3d operator-(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp -= Scalar;
		return Temp;
	}

	inline Pnt3d operator*(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp *= Scalar;
		return Temp;
	}

	inline Pnt3d operator*(const Standard_Real Scalar, const Pnt3d& P1)
	{
		Pnt3d Temp = P1;
		Temp *= Scalar;
		return Temp;
	}

	inline Pnt3d operator/(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp /= Scalar;
		return Temp;
	}

	inline Pnt3d CrossProduct(const Pnt3d & v1, const Pnt3d & v2)
	{
		return{ v1.Y() * v2.Z() - v2.Y() * v1.Z(), v1.Z() * v2.X() - v1.X() * v2.Z(), v1.X() * v2.Y() - v2.X() * v1.Y() };
	}

	inline Standard_Real DotProduct(const Pnt3d & P1, const Pnt3d & P2)
	{
		return P1.X()*P2.X() + P1.Y()*P2.Y() + P1.Z()*P2.Z();
	}

	inline Standard_Real Distance(const Pnt3d& P1, const Pnt3d& P2)
	{
		return P1.Distance(P2);
	}

	inline Standard_Real SquareDistance(const Pnt3d& P1, const Pnt3d& P2)
	{
		return P1.SquareDistance(P2);
	}
}