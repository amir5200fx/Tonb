#include <Istream.hxx>

#include <bool.hxx>
#include <token.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Set t to the put back token if there is one and return true,
// otherwise return false
bool tnbLib::Istream::getBack(token& t)
{
	if (bad())
	{
		FatalIOErrorIn("void Istream::getBack(token&)", *this)
			<< "Attempt to get back from bad stream"
			<< exit(FatalIOError);

		return false;
	}
	else if (putBack_)
	{
		t = putBackToken_;
		putBack_ = false;
		return true;
	}

	return false;
}


// Keep the put back token
void tnbLib::Istream::putBack(const token& t)
{
	if (bad())
	{
		FatalIOErrorIn("void Istream::putBack(const token&)", *this)
			<< "Attempt to put back onto bad stream"
			<< exit(FatalIOError);
	}
	else if (putBack_)
	{
		FatalIOErrorIn("void Istream::putBack(const token&)", *this)
			<< "Attempt to put back another token"
			<< exit(FatalIOError);
	}
	else
	{
		putBackToken_ = t;
		putBack_ = true;
	}
}


// Functions for reading object delimiters ( ... )

tnbLib::Istream& tnbLib::Istream::readBegin(const char* funcName)
{
	token delimiter(*this);
	if (delimiter != token::BEGIN_LIST)
	{
		setBad();
		FatalIOErrorIn("Istream::readBegin(const char*)", *this)
			<< "Expected a '" << token::BEGIN_LIST
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);
	}

	return *this;
}


tnbLib::Istream& tnbLib::Istream::readEnd(const char* funcName)
{
	token delimiter(*this);
	if (delimiter != token::END_LIST)
	{
		setBad();
		FatalIOErrorIn("Istream::readEnd(const char*)", *this)
			<< "Expected a '" << token::END_LIST
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);
	}

	return *this;
}


tnbLib::Istream& tnbLib::Istream::readEndBegin(const char* funcName)
{
	readEnd(funcName);
	return readBegin(funcName);
}


// Functions for reading List delimiters ( ... ) or { ... }

char tnbLib::Istream::readBeginList(const char* funcName)
{
	token delimiter(*this);

	if (delimiter != token::BEGIN_LIST && delimiter != token::BEGIN_BLOCK)
	{
		setBad();
		FatalIOErrorIn("Istream::readBeginList(const char*)", *this)
			<< "Expected a '" << token::BEGIN_LIST
			<< "' or a '" << token::BEGIN_BLOCK
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);

		return '\0';
	}

	return delimiter.pToken();
}


char tnbLib::Istream::readEndList(const char* funcName)
{
	token delimiter(*this);

	if (delimiter != token::END_LIST && delimiter != token::END_BLOCK)
	{
		setBad();
		FatalIOErrorIn("Istream::readEndList(const char*)", *this)
			<< "Expected a '" << token::END_LIST
			<< "' or a '" << token::END_BLOCK
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);

		return '\0';
	}

	return delimiter.pToken();
}


tnbLib::Istream& tnbLib::Istream::operator()() const
{
	if (!good())
	{
		check("Istream::operator()");
		FatalIOError.exit();
	}

	return const_cast<Istream&>(*this);
}


// ************************************************************************* //