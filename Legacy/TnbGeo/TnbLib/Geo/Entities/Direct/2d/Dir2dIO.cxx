#include <Dir2d.hxx>

#include <token.hxx>
#include <TnbError.hxx>
#include <errorManip.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <ISstream.hxx>

namespace tnbLib
{

	TnbGeo_EXPORT std::ostream & tnbLib::operator<<(std::ostream & os, const Dir2d & d)
	{
		os << d.X() << ",  " << d.Y();
		return os;
	}

	TnbGeo_EXPORT std::istream & tnbLib::operator>>(std::istream & is, Dir2d & d)
	{
		Standard_Real x, y;
		std::string comma;

		is >> x;
		if (!is.good())
		{
			FatalErrorIn("std::istream & operator>>(std::istream & is, Dir2d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn("std::istream & operator>>(std::istream & is, Dir2d & P)")
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> y;
		if (!is.good())
		{
			FatalErrorIn("std::istream & operator>>(std::istream & is, Dir2d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		d.SetCoord(x, y);
		return is;
	}

	TnbGeo_EXPORT Ostream & tnbLib::operator<<(Ostream & os, const Dir2d & d)
	{
		os << token::BEGIN_LIST;
		os << d.X() << token::COMMA << token::SPACE << d.Y();
		os << token::END_LIST;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Dir2d & d)");
		return os;
	}

	TnbGeo_EXPORT Istream & tnbLib::operator>>(Istream & is, Dir2d & d) 
	{
		Standard_Real x, y;
		string comma;

		is.readBegin("Istream & operator>>(Istream & is, const Dir2d & d)");
		is >> x >> comma >> y;
		is.readEnd("Istream & operator>>(Istream & is, const Dir2d & d)");

		d = Dir2d(x, y);

		// Check state of Istream
		is.check("Istream & operator>>(Istream & is, const Dir2d & d)");
		return is;
	}
}