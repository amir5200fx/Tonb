#include <IPstream.hxx>

#include <token.hxx>

#include <cctype>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Istream& IPstream::read(token& t)
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
			word* wPtr = new word;
			if (read(*wPtr))
			{
				if (token::compound::isCompound(*wPtr))
				{
					t = token::compound::New(*wPtr, *this).ptr();
					delete wPtr;
				}
				else
				{
					t = wPtr;
				}
			}
			else
			{
				delete wPtr;
				t.setBad();
			}
			return *this;
		}

		// String
		case token::STRING:
		{
			string* sPtr = new string;
			if (read(*sPtr))
			{
				t = sPtr;
			}
			else
			{
				delete sPtr;
				t.setBad();
			}
			return *this;
		}

		// Label
		case token::LABEL:
		{
			label l;
			if (read(l))
			{
				t = l;
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
			floatScalar s;
			if (read(s))
			{
				t = s;
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
			doubleScalar s;
			if (read(s))
			{
				t = s;
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


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //