#pragma once
namespace tnbLib
{

	template<class T>
	Ostream & operator<<(Ostream & os, const Marine_DimensionedParam<T>& p)
	{
		os << p.Name() << token::COLON << p() 
			<< token::COMMA << token::SPACE << token::BEGIN_SQR
			<< p.Dimension()[0] << token::COMMA
			<< p.Dimension()[1] << token::COMMA
			<< p.Dimension()[2] << token::COMMA
			<< p.Dimension()[3] << token::COMMA
			<< p.Dimension()[4] << token::COMMA
			<< p.Dimension()[5] << token::COMMA
			<< p.Dimension()[6] << token::END_SQR;
		return os;
	}

	/*template<class T>
	Ostream & operator>>(Ostream & os, Marine_DimensionedParam<T>& p)
	{
		word name;
		T value;
		scalar d0, d1, d2, d3, d4, d5, d6;
		char dummy;

		os >> name;
		os >> dummy;
		os >> value;
		os >> dummy;
		os >> dummy;
		os >> d0 >> dummy;
		os >> d1 >> dummy;
		os >> d2 >> dummy;
		os >> d3 >> dummy;
		os >> d4 >> dummy;
		os >> d5 >> dummy;
		os >> d6 >> dummy;

		dimensionSet set(d0, d1, d2, d3, d4, d5, d6);
		p = Marine_DimensionedParam<T>(name, set, value);
	}*/
}