#pragma once
inline std::tuple<Standard_Real, Standard_Real> 
tnbLib::Pnt2d::Components() const
{
	return { X(), Y() };
}

namespace tnbLib
{

	inline Pnt2d operator+(const Pnt2d& P1, const Pnt2d& P2)
	{
		Pnt2d Temp = P1;
		Temp += P2;
		return Temp;
	}

	inline Pnt2d operator-(const Pnt2d& P1, const Pnt2d& P2)
	{
		auto Temp = P1;
		Temp -= P2;
		return Temp;
	}

	inline Pnt2d operator+(const Pnt2d& P1, const Standard_Real Scalar)
	{
		Pnt2d Temp = P1;
		Temp += Scalar;
		return Temp;
	}

	inline Pnt2d operator+(const Standard_Real Scalar, const Pnt2d& P1)
	{
		Pnt2d Temp = P1;
		Temp += Scalar;
		return Temp;
	}

	inline Pnt2d operator-(const Pnt2d& P1, const Standard_Real Scalar)
	{
		Pnt2d Temp = P1;
		Temp -= Scalar;
		return Temp;
	}

	inline Pnt2d operator*(const Pnt2d& P1, const Standard_Real Scalar)
	{
		Pnt2d Temp = P1;
		Temp *= Scalar;
		return Temp;
	}

	inline Pnt2d operator*(const Standard_Real Scalar, const Pnt2d& P1)
	{
		Pnt2d Temp = P1;
		Temp *= Scalar;
		return Temp;
	}

	inline Pnt2d operator/(const Pnt2d& P1, const Standard_Real Scalar)
	{
		Pnt2d Temp = P1;
		Temp /= Scalar;
		return Temp;
	}

	inline Standard_Real Distance(const Pnt2d& P1, const Pnt2d& P2)
	{
		return P1.Distance(P2);
	}

	inline Standard_Real SquareDistance(const Pnt2d& P1, const Pnt2d& P2)
	{
		return P1.SquareDistance(P2);
	}

	inline Standard_Real DotProduct(const Pnt2d & P1, const Pnt2d & P2)
	{
		return P1.X()*P2.X() + P1.Y()*P2.Y();
	}

	inline Standard_Real CrossProduct(const Pnt2d & P1, const Pnt2d & P2)
	{
		return P1.X()*P2.Y() - P2.X()*P1.Y();
	}
}