#include <doubleScalar.hxx>

#include <token.hxx>
#include <Istream.hxx>

#include <sstream>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const char* const pTraits<doubleScalar>::typeName = "scalar";
	const doubleScalar pTraits<doubleScalar>::zero = 0.0;
	const doubleScalar pTraits<doubleScalar>::one = 1.0;
	const doubleScalar pTraits<doubleScalar>::min = -doubleScalarVSMALL;
	const doubleScalar pTraits<doubleScalar>::max = doubleScalarVGREAT;

	const char* pTraits<doubleScalar>::componentNames[] = { "x" };

	pTraits<doubleScalar>::pTraits(Istream& is)
	{
		is >> p_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	word name(const doubleScalar val)
	{
		std::ostringstream buf;
		buf << val;
		return buf.str();
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	doubleScalar readDoubleScalar(Istream& is)
	{
		doubleScalar rs;
		is >> rs;

		return rs;
	}


	Istream& operator>>(Istream& is, doubleScalar& s)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isNumber())
		{
			s = t.number();
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, doubleScalar&)", is)
				<< "wrong token type - expected doubleScalar found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, doubleScalar&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const doubleScalar s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const doubleScalar&)");
		return os;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib