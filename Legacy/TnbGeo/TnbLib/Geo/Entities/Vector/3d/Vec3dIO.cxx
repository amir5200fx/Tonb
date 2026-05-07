#include <Vec3d.hxx>

#include <token.hxx>
#include <TnbError.hxx>
#include <errorManip.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <ISstream.hxx>

namespace tnbLib
{

	TnbGeo_EXPORT std::ostream & tnbLib::operator<<(std::ostream & os, const Vec3d & d)
	{
		os << d.X() << ",  " << d.Y() << ",  " << d.Z();
		return os;
	}

	TnbGeo_EXPORT std::istream & tnbLib::operator>>(std::istream & is, Vec3d & d)
	{
		Standard_Real x, y, z;
		std::string comma;

		is >> x;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Dir3d &)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Dir3d &)")
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> y;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Dir3d &)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Dir3d &)")
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> z;
		if (!is.good())
		{
			FatalErrorIn("std::istream & tnbLib::operator>>(std::istream & is, Dir3d &)")
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		d.SetCoord(x, y, z);
		return is;
	}

	TnbGeo_EXPORT Ostream & tnbLib::operator<<(Ostream & os, const Vec3d & d)
	{
		os << token::BEGIN_LIST;
		os
			<< d.X()
			<< token::COMMA
			<< token::SPACE
			<< d.Y()
			<< token::COMMA
			<< token::SPACE
			<< d.Z();
		os << token::END_LIST;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Dir3d & d)");
		return os;
	}

	TnbGeo_EXPORT Istream & tnbLib::operator>>(Istream & is, Vec3d & d)
	{
		Standard_Real x, y, z;
		string comma;

		is.readBegin("Istream & tnbLib::operator>>(Istream & is, Dir3d & d)");
		is >> x >> comma >> y >> comma >> z;
		is.readEnd("Istream & tnbLib::operator>>(Istream & is, Dir3d & d)");

		d = Vec3d(x, y, z);
		// Check state of Istream
		is.check("Istream & tnbLib::operator>>(Istream & is, Dir3d & d)");
		return is;
	}
}