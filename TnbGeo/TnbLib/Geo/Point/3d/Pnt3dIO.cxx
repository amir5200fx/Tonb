#include <Pnt3d.hxx>

#include <token.hxx>
#include <OFstream.hxx>
#include <Istream.hxx>

void tnbLib::Pnt3d::Print(std::ostream & os) const
{
	os << *this;
}

void tnbLib::Pnt3d::AddToPlt(OFstream & theFile) const
{
	theFile << X() << "  " << Y() << "  " << Z();
}

namespace tnbLib
{

	std::ostream & operator<<(std::ostream & os, const Pnt3d & P)
	{
		os << P.X() << ",  " << P.Y() << ",  " << P.Z();
		return os;
	}

	std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)
	{
		Standard_Real x, y, z;
		std::string comma;

		is >> x;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)")
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> y;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)")
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> z;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		P.SetCoord(x, y, z);
		return is;
	}

	Ostream & operator<<(Ostream & os, const Pnt3d & P)
	{
		os << token::BEGIN_LIST;
		os
			<< P.X()
			<< token::COMMA
			<< token::SPACE
			<< P.Y()
			<< token::COMMA
			<< token::SPACE
			<< P.Z();
		os << token::END_LIST;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Pnt3d & P)");
		return os;
	}

	Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)
	{
		Standard_Real x, y, z;
		string comma;

		is.readBegin("Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)");
		is >> x >> comma >> y >> comma >> z;
		is.readEnd("Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)");

		// Check state of Istream
		is.check("Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)");
		return is;
	}
}