#include <GeoIO_INPElement_B31.hxx>

const char* tnbLib::GeoIO_INPElement_B31::typeName_ = "B31";

namespace tnbLib
{

	TnbGeo_EXPORT Istream& operator>>(Istream& is, GeoIO_INPElement_B31& elm)
	{
		Standard_Integer id, i0, i1;
		string comma;
		is.readBegin("Istream& operator>>(Istream& is, GeoIO_INPElement_B31& elm)");
		is >> id >> comma >> i0 >> comma >> i1 >> comma;
		is.readEnd("Istream& operator>>(Istream& is, GeoIO_INPElement_B31& elm)");

		elm = GeoIO_INPElement_B31(id, { i0,i1 });
		// Check state of Istream
		is.check("Istream& operator>>(Istream& is, GeoIO_INPElement_B31& elm)");
		return is;
	}

	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, GeoIO_INPElement_B31& elm)
	{
		Standard_Integer id, i0, i1;
		string comma;
		is >> id >> comma >> i0 >> comma >> i1 >> comma;

		elm = GeoIO_INPElement_B31(id, { i0,i1 });
		if (is.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "Unable to read the point" << endl
				<< abort(FatalError);
		}
		return is;
	}
}

tnbLib::GeoIO_INPElement_B31::GeoIO_INPElement_B31(Istream& is)
{
	is >> *this;
}

tnbLib::GeoIO_INPElement_B31::GeoIO_INPElement_B31(std::istream& is)
{
	is >> *this;
}

tnbLib::word 
tnbLib::GeoIO_INPElement_B31::ElementType() const
{
	return word(typeName_);
}

Standard_Integer 
tnbLib::GeoIO_INPElement_B31::NbPoints() const
{
	return Standard_Integer(nbPoints);
}

std::vector<Standard_Integer> 
tnbLib::GeoIO_INPElement_B31::RetrieveIndices() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoIO_INPElement_B31);