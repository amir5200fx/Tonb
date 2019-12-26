#include <ITstream.hxx>

#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::ITstream::print(Ostream& os) const
{
	os << "ITstream : " << name_.c_str();

	if (size())
	{
		if (begin()->lineNumber() == rbegin()->lineNumber())
		{
			os << ", line " << begin()->lineNumber() << ", ";
		}
		else
		{
			os << ", lines " << begin()->lineNumber()
				<< '-' << rbegin()->lineNumber() << ", ";
		}
	}
	else
	{
		os << ", line " << lineNumber() << ", ";
	}

	IOstream::print(os);
}


tnbLib::Istream& tnbLib::ITstream::read(token& t)
{
	// Return the put back token if it exists
	if (Istream::getBack(t))
	{
		lineNumber_ = t.lineNumber();
		return *this;
	}

	if (tokenIndex_ < size())
	{
		t = operator[](tokenIndex_++);
		lineNumber_ = t.lineNumber();

		if (tokenIndex_ == size())
		{
			setEof();
		}
	}
	else
	{
		if (eof())
		{
			FatalIOErrorIn
			(
				"ITstream::read(token& t)",
				*this
			) << "attempt to read beyond EOF"
				<< exit(FatalIOError);

			setBad();
		}
		else
		{
			setEof();
		}

		if (size())
		{
			token::undefinedToken.lineNumber()
				= operator[](size() - 1).lineNumber();
		}
		else
		{
			token::undefinedToken.lineNumber() = lineNumber();
		}

		t = token::undefinedToken;
	}

	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(char&)
{
	notImplemented("Istream& ITstream::read(char& c)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(word&)
{
	notImplemented("Istream& ITstream::read(word&)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(string&)
{
	notImplemented("Istream& ITstream::read(string&)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(label&)
{
	notImplemented("Istream& ITstream::read(label&)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(floatScalar&)
{
	notImplemented("Istream& ITstream::read(floatScalar&)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(doubleScalar&)
{
	notImplemented("Istream& ITstream::read(doubleScalar&)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(longDoubleScalar&)
{
	notImplemented("Istream& ITstream::read(longDoubleScalar&)");
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(char*, std::streamsize)
{
	notImplemented("Istream& ITstream::read(char*, std::streamsize)");
	return *this;
}


// Rewind the token stream so that it may be read again
tnbLib::Istream& tnbLib::ITstream::rewind()
{
	tokenIndex_ = 0;

	if (size())
	{
		lineNumber_ = operator[](0).lineNumber();
	}

	setGood();

	return *this;
}


// ************************************************************************* //