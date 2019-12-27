#include <OSstream.hxx>

#include <token.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::OSstream::write(const token&)
{
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const char c)
{
	os_ << c;
	if (c == token::NL)
	{
		lineNumber_++;
	}
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const char* str)
{
	lineNumber_ += string(str).count(token::NL);
	os_ << str;
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const word& str)
{
	os_ << str;
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const string& str)
{
	os_ << token::BEGIN_STRING;

	register int backslash = 0;
	for (string::const_iterator iter = str.begin(); iter != str.end(); ++iter)
	{
		register char c = *iter;

		if (c == '\\')
		{
			backslash++;
			// suppress output until we know if other characters follow
			continue;
		}
		else if (c == token::NL)
		{
			lineNumber_++;
			backslash++;    // backslash escape for newline
		}
		else if (c == token::END_STRING)
		{
			backslash++;    // backslash escape for quote
		}

		// output pending backslashes
		while (backslash)
		{
			os_ << '\\';
			backslash--;
		}

		os_ << c;
	}

	// silently drop any trailing backslashes
	// they would otherwise appear like an escaped end-quote

	os_ << token::END_STRING;

	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::writeQuoted
(
	const std::string& str,
	const bool quoted
)
{
	if (quoted)
	{
		os_ << token::BEGIN_STRING;

		register int backslash = 0;
		for
			(
				string::const_iterator iter = str.begin();
				iter != str.end();
				++iter
				)
		{
			register char c = *iter;

			if (c == '\\')
			{
				backslash++;
				// suppress output until we know if other characters follow
				continue;
			}
			else if (c == token::NL)
			{
				lineNumber_++;
				backslash++;    // backslash escape for newline
			}
			else if (c == token::END_STRING)
			{
				backslash++;    // backslash escape for quote
			}

			// output pending backslashes
			while (backslash)
			{
				os_ << '\\';
				backslash--;
			}

			os_ << c;
		}

		// silently drop any trailing backslashes
		// they would otherwise appear like an escaped end-quote
		os_ << token::END_STRING;
	}
	else
	{
		// output unquoted string, only advance line number on newline
		lineNumber_ += string(str).count(token::NL);
		os_ << str;
	}

	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const label val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const floatScalar val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const doubleScalar val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const longDoubleScalar val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


tnbLib::Ostream& tnbLib::OSstream::write(const char* buf, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalIOErrorIn("Ostream::write(const char*, std::streamsize)", *this)
			<< "stream format not binary"
			<< abort(FatalIOError);
	}

	os_ << token::BEGIN_LIST;
	os_.write(buf, count);
	os_ << token::END_LIST;

	setState(os_.rdstate());

	return *this;
}


void tnbLib::OSstream::indent()
{
	for (register unsigned short i = 0; i < indentLevel_*indentSize_; i++)
	{
		os_ << ' ';
	}
}


void tnbLib::OSstream::flush()
{
	os_.flush();
}


// Add carriage return and flush stream
void tnbLib::OSstream::endl()
{
	write('\n');
	os_.flush();
}


// Get flags of output stream
std::ios_base::fmtflags tnbLib::OSstream::flags() const
{
	return os_.flags();
}


// Set flags of output stream
std::ios_base::fmtflags tnbLib::OSstream::flags(const ios_base::fmtflags f)
{
	return os_.flags(f);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// Get width of output field
int tnbLib::OSstream::width() const
{
	return os_.width();
}

// Set width of output field (and return old width)
int tnbLib::OSstream::width(const int w)
{
	return os_.width(w);
}

// Get precision of output field
int tnbLib::OSstream::precision() const
{
	return os_.precision();
}

// Set precision of output field (and return old precision)
int tnbLib::OSstream::precision(const int p)
{
	return os_.precision(p);
}


// ************************************************************************* //