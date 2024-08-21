#pragma once
#ifndef _Pnt2d_Header
#define _Pnt2d_Header

#include <gp_Pnt2d.hxx>
#include <IOstream.hxx>
#include <Geo_Module.hxx>
#include <Geo_Serialization.hxx>
#include <Global_ChaiscriptFwd.hxx>

#include <sstream>

namespace tnbLib
{

	//Forward Declarations
	class Pnt2d;
	class OFstream;


	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Pnt2d&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Pnt2d&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Pnt2d&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Pnt2d&);

	TnbGeo_EXPORT Pnt2d operator-(const Pnt2d& P1, const Pnt2d& P2);

	namespace chai
	{
		TnbGeo_EXPORT void add_pnt_2d(const module_t&);
	}

	class Pnt2d
		: public gp_Pnt2d
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<gp_Pnt2d>(*this);
		}

		//TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		typedef Pnt2d ptType;

		//- Static members
		static TnbGeo_EXPORT const int nbCmpts;
		static TnbGeo_EXPORT const Pnt2d null;

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

		inline std::tuple<Standard_Real, Standard_Real>
			Components() const;

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

		TnbGeo_EXPORT void Print(std::ostream& os = std::cout) const;

		TnbGeo_EXPORT void AddToPlt(OFstream& theFile) const;
		TnbGeo_EXPORT void AddToPlt(std::stringstream& theStream) const;
	};
}

#include <Pnt2dI.hxx>

#endif // !_Pnt2d_Header
