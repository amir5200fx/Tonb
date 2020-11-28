#include <Pnt2d.hxx>

#include <token.hxx>
#include <TnbError.hxx>
#include <errorManip.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <ISstream.hxx>

#include <string>

void tnbLib::Pnt2d::Print(std::ostream & os) const
{
	os << *this;

}

void tnbLib::Pnt2d::AddToPlt(OFstream & theFile) const
{
	theFile << X() << "  " << Y();
}

namespace tnbLib
{

	TnbGeo_EXPORT std::ostream & operator<<(std::ostream & os, const Pnt2d & P)
	{
		os << P.X() << ",  " << P.Y();
		return os;
	}

	TnbGeo_EXPORT std::istream & operator>>(std::istream & is, Pnt2d & P)
	{
		Standard_Real x, y;
		std::string comma;

		is >> x;
		if (!is.good())
		{
			FatalErrorIn("std::istream & operator>>(std::istream & is, Pnt2d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn("std::istream & operator>>(std::istream & is, Pnt2d & P)")
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> y;
		if (!is.good())
		{
			FatalErrorIn("std::istream & operator>>(std::istream & is, Pnt2d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		P.SetCoord(x, y);
		return is;
	}

	TnbGeo_EXPORT Ostream & operator<<(Ostream & os, const Pnt2d & P)
	{
		os << token::BEGIN_LIST;
		os << P.X() << token::COMMA << token::SPACE << P.Y();
		os << token::END_LIST;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Pnt2d & P)");
		return os;
	}

	TnbGeo_EXPORT Istream & operator>>(Istream & is, Pnt2d & P)
	{
		Standard_Real x, y;
		string comma;

		is.readBegin("Istream & operator>>(Istream & is, Pnt2d & P)");
		is >> x >> comma >> y;
		is.readEnd("Istream & operator>>(Istream & is, Pnt2d & P)");

		P.X() = x;
		P.Y() = y;

		// Check state of Istream
		is.check("Istream & operator>>(Istream & is, Pnt2d & P)");
		return is;
	}
}

//TNB_SAVE_IMPLEMENTATION(tnbLib::Pnt2d)
//{
//	ar << X();
//	ar << Y();
//}
//
//TNB_LOAD_IMPLEMENTATION(tnbLib::Pnt2d)
//{
//	ar >> X();
//	ar >> Y();
//}