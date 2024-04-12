#pragma once
#ifndef _Pnt3d_Header
#define _Pnt3d_Header

#include <gp_Pnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Geo_Module.hxx>
#include <Geo_Serialization.hxx>

#include <sstream>

namespace tnbLib
{

	//Forward Declarations
	class Pnt3d;
	class OFstream;

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Pnt3d&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Pnt3d&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Pnt3d&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Pnt3d&);

	TnbGeo_EXPORT Pnt3d operator-(const Pnt3d& P1, const Pnt3d& P2);

	class Pnt3d
		: public gp_Pnt
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<gp_Pnt>(*this);
		}

		//TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		typedef Pnt3d ptType;

		//- Static members
		static TnbGeo_EXPORT const int nbCmpts;
		static TnbGeo_EXPORT const Pnt3d null;

		enum
		{
			dim = 3
		};

		// constructors

		Pnt3d()
		{}

		Pnt3d
		(
			const Standard_Real theX,
			const Standard_Real theY,
			const Standard_Real theZ
		)
			: gp_Pnt(theX, theY, theZ)
		{}

		Pnt3d(const gp_XYZ& XYZ)
			: gp_Pnt(XYZ)
		{}

		Pnt3d(const gp_Pnt& Pt)
			: gp_Pnt(Pt)
		{}

		Pnt3d(std::istream& is)
		{
			is >> *this;
		}

		Pnt3d(Istream& is)
		{
			is >> *this;
		}

		Standard_Real X() const
		{
			return gp_Pnt::Coord().X();
		}

		Standard_Real& X()
		{
			return gp_Pnt::ChangeCoord().ChangeCoord(1);
		}

		Standard_Real Y() const
		{
			return gp_Pnt::Coord().Y();
		}

		Standard_Real& Y()
		{
			return gp_Pnt::ChangeCoord().ChangeCoord(2);
		}

		Standard_Real Z() const
		{
			return gp_Pnt::Coord().Z();
		}

		Standard_Real& Z()
		{
			return gp_Pnt::ChangeCoord().ChangeCoord(3);
		}

		Standard_Real TwoNorm() const
		{
			return sqrt(X()*X() + Y()*Y() + Z()*Z());
		}

		Standard_Real SquareTwoNorm() const
		{
			return X()*X() + Y()*Y() + Z()*Z();
		}

		Pnt3d& operator+=(const Pnt3d& theOther)
		{
			X() += theOther.X();
			Y() += theOther.Y();
			Z() += theOther.Z();

			return *this;
		}

		Pnt3d& operator-=(const Pnt3d& theOther)
		{
			X() -= theOther.X();
			Y() -= theOther.Y();
			Z() -= theOther.Z();

			return *this;
		}

		Pnt3d& operator*=(const Pnt3d& theOther)
		{
			X() *= theOther.X();
			Y() *= theOther.Y();
			Z() *= theOther.Z();

			return *this;
		}

		Pnt3d& operator=(const Standard_Real Scalar)
		{
			X() = Scalar;
			Y() = Scalar;
			Z() = Scalar;

			return *this;
		}

		Pnt3d& operator+=(const Standard_Real Scalar)
		{
			X() += Scalar;
			Y() += Scalar;
			Z() += Scalar;

			return *this;
		}

		Pnt3d& operator-=(const Standard_Real Scalar)
		{
			X() -= Scalar;
			Y() -= Scalar;
			Z() -= Scalar;

			return *this;
		}

		Pnt3d& operator*=(const Standard_Real Scalar)
		{
			X() *= Scalar;
			Y() *= Scalar;
			Z() *= Scalar;

			return *this;
		}

		Pnt3d& operator/=(const Standard_Real Scalar)
		{
			X() /= Scalar;
			Y() /= Scalar;
			Z() /= Scalar;

			return *this;
		}

		Pnt3d& operator+()
		{
			return *this;
		}

		Pnt3d operator-()
		{
			return Pnt3d() - *this;
		}

		Pnt3d Normalized() const
		{
			auto Copy = *this;
			Copy.Normalize();
			return std::move(Copy);
		}

		inline std::tuple<Standard_Real, Standard_Real, Standard_Real>
			Components() const;

		void Normalize()
		{
			Standard_Real d = TwoNorm();
			if (d <= gp::Resolution())
			{
				FatalErrorIn("void Normalize()")
					<< " Length of the vector is too small : " << d
					<< abort(FatalError);
			}
			X() /= d;
			Y() /= d;
			Z() /= d;
		}

		void Get
		(
			Standard_Real& theX,
			Standard_Real& theY,
			Standard_Real& theZ
		) const
		{
			theX = X();
			theY = Y();
			theZ = Z();
		}

		//- IO functions and operators

		TnbGeo_EXPORT void Print(std::ostream& os = std::cout) const;

		TnbGeo_EXPORT void AddToPlt(OFstream& theFile) const;
		TnbGeo_EXPORT void AddToPlt(std::stringstream& theStream) const;
	};
}

#include <Pnt3dI.hxx>

#endif // !_Pnt3d_Header
