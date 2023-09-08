#include <GeoIO_INPElement_CPS3.hxx>

const char* tnbLib::GeoIO_INPElement_CPS3::typeName_ = "CPS3";

namespace tnbLib
{

	TnbGeo_EXPORT Istream& operator>>(Istream& is, GeoIO_INPElement_CPS3& elm)
	{
		Standard_Integer id, i0, i1, i2;
		string comma;

		is.readBegin("Istream& operator>>(Istream& is, GeoIO_INPElement_CPS3& elm)");
		is >> id >> comma >> i0 >> comma >> i1 >> comma >> i2;
		is.readEnd("Istream& operator>>(Istream& is, GeoIO_INPElement_CPS3& elm)");

		elm = GeoIO_INPElement_CPS3(id, { i0,i1,i2 });
		// Check state of Istream
		is.check("Istream& operator>>(Istream& is, GeoIO_INPElement_CPS3& elm)");
		return is;
	}

	TnbGeo_EXPORT std::istream& tnbLib::operator>>(std::istream& is, GeoIO_INPElement_CPS3& elm)
	{
		Standard_Integer id, i0, i1, i2;
		string comma;

		is >> id >> comma >> i0 >> comma >> i1 >> comma >> i2;
		{// flush the line [9/6/2023 aamir]
			std::string line;
			std::getline(is, line);
		}
		elm = GeoIO_INPElement_CPS3(id, { i0,i1,i2 });
		if (is.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "Unable to read the point" << endl
				<< abort(FatalError);
		}
		return is;
	}
}

tnbLib::GeoIO_INPElement_CPS3::GeoIO_INPElement_CPS3(Istream& is)
{
	is >> *this;
}

tnbLib::GeoIO_INPElement_CPS3::GeoIO_INPElement_CPS3(std::istream& is)
{
	is >> *this;
}

tnbLib::word 
tnbLib::GeoIO_INPElement_CPS3::ElementType() const
{
	return word(typeName_);
}

Standard_Integer 
tnbLib::GeoIO_INPElement_CPS3::NbPoints() const
{
	return Standard_Integer(nbPoints);
}

std::vector<Standard_Integer> 
tnbLib::GeoIO_INPElement_CPS3::RetrieveIndices() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoIO_INPElement_CPS3);