#pragma once
#ifndef _Pnt2d_Header
#define _Pnt2d_Header

#include <gp_Pnt2d.hxx>
#include <IOstream.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	//Forward Declarations
	class Pnt2d;
	class OFstream;


	std::ostream& operator<<(std::ostream& os, const Pnt2d&);
	std::istream& operator>>(std::istream& is, Pnt2d&);

	Ostream& operator<<(Ostream& os, const Pnt2d&);
	Istream& operator>>(Istream& is, Pnt2d&);

	Pnt2d operator-(const Pnt2d& P1, const Pnt2d& P2);

	class Pnt2d
		: public gp_Pnt2d
	{

		/*Private Data*/

		DECLARE_SAVE_LOAD_HEADER(TnbGeo_EXPORT);

	public:

		typedef Pnt2d ptType;

		//- Static members
		static const int nbCmpts;
		static const Pnt2d null;

		enum
		{
			dim = 2
		};

		// constructors

		Pnt2d()
		{}

		Pnt2d
		(
			const Standard_Real theX,
			const Standard_Real theY
		)
			: gp_Pnt2d(theX, theY)
		{}

		Pnt2d(const gp_Pnt2d& theOther)
			: gp_Pnt2d(theOther)
		{}

		Pnt2d(const gp_XY& XY)
			: gp_Pnt2d(XY)
		{}

		Pnt2d(std::istream& is)
		{
			is >> *this;
		}

		Pnt2d(Istream& is)
		{
			is >> *this;
		}

		Pnt2d& operator+=(const Pnt2d& theOther)
		{
			X() += theOther.X();
			Y() += theOther.Y();

			return *this;
		}

		Pnt2d& operator-=(const Pnt2d& theOther)
		{
			X() -= theOther.X();
			Y() -= theOther.Y();

			return *this;
		}

		Pnt2d& operator*=(const Pnt2d& theOther)
		{
			X() *= theOther.X();
			Y() *= theOther.Y();

			return *this;
		}

		Pnt2d& operator=(const Standard_Real Scalar)
		{
			X() = Scalar;
			Y() = Scalar;

			return *this;
		}

		Pnt2d& operator+=(const Standard_Real Scalar)
		{
			X() += Scalar;
			Y() += Scalar;

			return *this;
		}

		Pnt2d& operator-=(const Standard_Real Scalar)
		{
			X() -= Scalar;
			Y() -= Scalar;

			return *this;
		}

		Pnt2d& operator*=(const Standard_Real Scalar)
		{
			X() *= Scalar;
			Y() *= Scalar;

			return *this;
		}

		Pnt2d& operator/=(const Standard_Real Scalar)
		{
			X() /= Scalar;
			Y() /= Scalar;

			return *this;
		}

		Pnt2d& operator+()
		{
			return *this;
		}

		Pnt2d operator-()
		{
			return Pnt2d() - (*this);
		}

		void Rotate90ccw()
		{
			Standard_Real Temp = X();
			X() = -Y();
			Y() = Temp;
		}

		Standard_Real X() const
		{
			return gp_Pnt2d::Coord().X();
		}

		Standard_Real& X()
		{
			return gp_Pnt2d::ChangeCoord().ChangeCoord(1);
		}

		Standard_Real Y() const
		{
			return gp_Pnt2d::Coord().Y();
		}

		Standard_Real& Y()
		{
			return gp_Pnt2d::ChangeCoord().ChangeCoord(2);
		}

		Pnt2d UnitLength() const
		{
			Standard_Real S = 1.0 / TwoNorm();

			return Pnt2d(X()*S, Y()*S);
		}

		Standard_Real TwoNorm() const
		{
			return sqrt(X()*X() + Y()*Y());
		}

		Standard_Real SquareTwoNorm() const
		{
			return X()*X() + Y()*Y();
		}

		Standard_Real DotProduct(const Pnt2d& theOther) const
		{
			return X()*theOther.X() + Y()*theOther.Y();
		}

		void Get
		(
			Standard_Real& theX,
			Standard_Real& theY
		) const
		{
			theX = X();
			theY = Y();
		}

		//- IO functions and operators

		void Print(std::ostream& os = std::cout) const;

		void AddToPlt(OFstream& theFile) const;
	};
}

#include <Pnt2dI.hxx>

#endif // !_Pnt2d_Header
