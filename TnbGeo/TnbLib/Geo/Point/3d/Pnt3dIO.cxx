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

void tnbLib::Pnt3d::AddToPlt(std::fstream& file) const
{
	file << X() << " " << Y() << " " << Z();
}

void tnbLib::Pnt3d::AddToPlt(std::stringstream& theStream) const
{
	theStream << X() << " " << Y() << " " << Z();
}

namespace tnbLib
{

	TnbGeo_EXPORT std::ostream & operator<<(std::ostream & os, const Pnt3d & P)
	{
		os << P.X() << ",  " << P.Y() << ",  " << P.Z();
		return os;
	}

	TnbGeo_EXPORT std::istream & tnbLib::operator>>(std::istream & is, Pnt3d & P)
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

	TnbGeo_EXPORT Ostream & operator<<(Ostream & os, const Pnt3d & P)
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

	TnbGeo_EXPORT Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)
	{
		Standard_Real x, y, z;
		string comma;

		is.readBegin("Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)");
		is >> x >> comma >> y >> comma >> z;
		is.readEnd("Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)");

		P = Pnt3d(x, y, z);
		// Check state of Istream
		is.check("Istream & tnbLib::operator>>(Istream & is, Pnt3d & P)");
		return is;
	}
}

//TNB_SAVE_IMPLEMENTATION(tnbLib::Pnt3d)
//{
//	ar << X();
//	ar << Y();
//	ar << Z();
//}
//
//TNB_LOAD_IMPLEMENTATION(tnbLib::Pnt3d)
//{
//	ar >> X();
//	ar >> Y();
//	ar >> Z();
//}

