#include <SHA1Digest.hxx>

#include <IOstreams.hxx>

#include <cstring>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

//! @cond fileScope
const char hexChars[] = "0123456789abcdef";
//! @endcond fileScope


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SHA1Digest::SHA1Digest()
{
	clear();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::SHA1Digest::clear()
{
	memset(v_, 0, length);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

bool tnbLib::SHA1Digest::operator==(const SHA1Digest& rhs) const
{
	for (unsigned i = 0; i < length; ++i)
	{
		if (v_[i] != rhs.v_[i])
		{
			return false;
		}
	}

	return true;
}


bool tnbLib::SHA1Digest::operator!=(const SHA1Digest& rhs) const
{
	return !operator==(rhs);
}


// * * * * * * * * * * * * * * Friend Operators * * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const SHA1Digest& dig)
{
	const unsigned char *v = dig.v_;

	for (unsigned i = 0; i < dig.length; ++i)
	{
		os.write(hexChars[((v[i] >> 4) & 0xF)]);
		os.write(hexChars[(v[i] & 0xF)]);
	}

	os.check("Ostream& operator<<(Ostream&, const SHA1Digest&)");
	return os;
}


// ************************************************************************* //