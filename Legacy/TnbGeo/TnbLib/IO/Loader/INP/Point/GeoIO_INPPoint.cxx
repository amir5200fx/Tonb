#include <GeoIO_INPPoint.hxx>

namespace tnbLib
{

	TnbGeo_EXPORT Istream& tnbLib::operator>>(Istream& is, GeoIO_INPPoint& P)
	{
		Standard_Real x, y, z;
		string comma;
		Standard_Integer id;

		is.readBegin("Istream& tnbLib::operator>>(Istream& is, GeoIO_INPPoint& P)");
		is >> id >> comma >> x >> comma >> y >> comma >> z;
		is.readEnd("Istream& tnbLib::operator>>(Istream& is, GeoIO_INPPoint& P)");

		P = GeoIO_INPPoint(id, { x,y,z });
		// Check state of Istream
		is.check("Istream& tnbLib::operator>>(Istream& is, GeoIO_INPPoint& P)");
		return is;
	}

	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, GeoIO_INPPoint& P)
	{
		Standard_Real x, y, z;
		string comma;
		Standard_Integer id;
		is >> id >> comma >> x >> comma >> y >> comma >> z;
		P = GeoIO_INPPoint(id, { x,y,z });
		if (is.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "Unable to read the point" << endl
				<< abort(FatalError);
		}
		return is;
	}
}

tnbLib::GeoIO_INPPoint::GeoIO_INPPoint(Istream& is)
{
	is >> *this;
}

tnbLib::GeoIO_INPPoint::GeoIO_INPPoint(std::istream& is)
{
	is >> *this;
}