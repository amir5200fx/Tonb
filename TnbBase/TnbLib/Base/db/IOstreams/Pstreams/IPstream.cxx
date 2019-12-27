#include <IPstream.hxx>

#include <int.hxx>
#include <token.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <cctype>


// * * * * * * * * * * * * * Private member functions  * * * * * * * * * * * //

inline void tnbLib::IPstream::checkEof()
{
	if (bufPosition_ == messageSize_)
	{
		setEof();
	}
}


template<class T>
inline void tnbLib::IPstream::readFromBuffer(T& t)
{
	const size_t align = sizeof(T);
	bufPosition_ = align + ((bufPosition_ - 1) & ~(align - 1));

	t = reinterpret_cast<T&>(buf_[bufPosition_]);
	bufPosition_ += sizeof(T);
	checkEof();
}


inline void tnbLib::IPstream::readFromBuffer
(
	void* data,
	size_t count,
	size_t align
)
{
	if (align > 1)
	{
		bufPosition_ = align + ((bufPosition_ - 1) & ~(align - 1));
	}

	register const char* bufPtr = &buf_[bufPosition_];
	register char* dataPtr = reinterpret_cast<char*>(data);
	register size_t i = count;
	while (i--) *dataPtr++ = *bufPtr++;
	bufPosition_ += count;
	checkEof();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::IPstream::~IPstream()
{}



// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::IPstream::read(token& t)
{
	// Return the put back token if it exists
	if (Istream::getBack(t))
	{
		return *this;
	}

	char c;

	// return on error
	if (!read(c))
	{
		t.setBad();
		return *this;
	}

	// Set the line number of this token to the current stream line number
	t.lineNumber() = lineNumber();

	// Analyse input starting with this character.
	switch (c)
	{
		// Punctuation
	case token::END_STATEMENT:
	case token::BEGIN_LIST:
	case token::END_LIST:
	case token::BEGIN_SQR:
	case token::END_SQR:
	case token::BEGIN_BLOCK:
	case token::END_BLOCK:
	case token::COLON:
	case token::COMMA:
	case token::ASSIGN:
	case token::ADD:
	case token::SUBTRACT:
	case token::MULTIPLY:
	case token::DIVIDE:
	{
		t = token::punctuationToken(c);
		return *this;
	}

	// Word
	case token::WORD:
	{
		word* pval = new word;
		if (read(*pval))
		{
			if (token::compound::isCompound(*pval))
			{
				t = token::compound::New(*pval, *this).ptr();
				delete pval;
			}
			else
			{
				t = pval;
			}
		}
		else
		{
			delete pval;
			t.setBad();
		}
		return *this;
	}

	// String
	case token::STRING:
	{
		string* pval = new string;
		if (read(*pval))
		{
			t = pval;
		}
		else
		{
			delete pval;
			t.setBad();
		}
		return *this;
	}

	// Label
	case token::LABEL:
	{
		label val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// floatScalar
	case token::FLOAT_SCALAR:
	{
		floatScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// doubleScalar
	case token::DOUBLE_SCALAR:
	{
		doubleScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// longDoubleScalar
	case token::LONG_DOUBLE_SCALAR:
	{
		longDoubleScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// Character (returned as a single character word) or error
	default:
	{
		if (isalpha(c))
		{
			t = word(c);
			return *this;
		}

		setBad();
		t.setBad();

		return *this;
	}
	}
}


tnbLib::Istream& tnbLib::IPstream::read(char& c)
{
	c = buf_[bufPosition_];
	bufPosition_++;
	checkEof();
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(word& str)
{
	size_t len;
	readFromBuffer(len);
	str = &buf_[bufPosition_];
	bufPosition_ += len + 1;
	checkEof();
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(string& str)
{
	size_t len;
	readFromBuffer(len);
	str = &buf_[bufPosition_];
	bufPosition_ += len + 1;
	checkEof();
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(label& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(floatScalar& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(doubleScalar& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(longDoubleScalar& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::read(char* data, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalErrorIn("IPstream::read(char*, std::streamsize)")
			<< "stream format not binary"
			<< tnbLib::abort(FatalError);
	}

	readFromBuffer(data, count, 8);
	return *this;
}


tnbLib::Istream& tnbLib::IPstream::rewind()
{
	bufPosition_ = 0;
	return *this;
}


// ************************************************************************* //