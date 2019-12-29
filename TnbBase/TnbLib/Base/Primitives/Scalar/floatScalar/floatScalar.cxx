#include <floatScalar.hxx>

#include <token.hxx>
#include <Istream.hxx>

#include <sstream>

namespace tnbLib
{
	const char* const pTraits<floatScalar>::typeName = "scalar";
	const floatScalar pTraits<floatScalar>::zero = 0.0;
	const floatScalar pTraits<floatScalar>::one = 1.0;
	const floatScalar pTraits<floatScalar>::min = -floatScalarVSMALL;
	const floatScalar pTraits<floatScalar>::max = floatScalarVGREAT;

	const char* pTraits<floatScalar>::componentNames[] = { "x" };

	pTraits<floatScalar>::pTraits(Istream& is)
	{
		is >> p_;
	}

	word name(const floatScalar val)
	{
		std::ostringstream buf;
		buf << val;
		return buf.str();
	}

	floatScalar readFloatScalar(Istream& is)
	{
		floatScalar rs;
		is >> rs;

		return rs;
	}


	Istream& operator>>(Istream& is, floatScalar& s)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isNumber())
		{
			s = (floatScalar)t.number();
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, floatScalar&)", is)
				<< "wrong token type - expected floatScalar found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, floatScalar&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const floatScalar s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const floatScalar&)");
		return os;
	}

} // End namespace tnbLib