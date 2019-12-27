#include <primitiveEntry.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::primitiveEntry::primitiveEntry(const keyType& key, const ITstream& tokens)
	: entry(key)
	, ITstream(tokens)
{
	name() += "::" + keyword();
}


tnbLib::primitiveEntry::primitiveEntry(const keyType& keyword, const token& t)
	: entry(keyword)
	, ITstream(keyword, tokenList(1, t))
{}


tnbLib::primitiveEntry::primitiveEntry
(
	const keyType& keyword,
	const tokenList& tokens
)
	: entry(keyword)
	, ITstream(keyword, tokens)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::primitiveEntry::startLineNumber() const
{
	if (size())
	{
		return operator[](0).lineNumber();
	}
	else
	{
		return -1;
	}
}

tnbLib::label tnbLib::primitiveEntry::endLineNumber() const
{
	if (size())
	{
		return operator[](size() - 1).lineNumber();
	}
	else
	{
		return -1;
	}
}


tnbLib::ITstream& tnbLib::primitiveEntry::stream() const
{
	ITstream& dataStream = const_cast<primitiveEntry&>(*this);
	dataStream.rewind();
	return dataStream;
}


const tnbLib::dictionary& tnbLib::primitiveEntry::dict() const
{
	FatalErrorIn("const dictionary& primitiveEntry::dict() const")
		<< "Attempt to return primitive entry " << info()
		<< " as a sub-dictionary"
		<< abort(FatalError);

	return dictionary::null;
}


tnbLib::dictionary& tnbLib::primitiveEntry::dict()
{
	FatalErrorIn("const dictionary& primitiveEntry::dict()")
		<< "Attempt to return primitive entry " << info()
		<< " as a sub-dictionary"
		<< abort(FatalError);

	return const_cast<dictionary&>(dictionary::null);
}


void tnbLib::primitiveEntry::insert
(
	const tokenList& varTokens,
	const label posI
)
{
	tokenList& tokens = *this;

	if (varTokens.empty())
	{
		label end = tokens.size() - 1;

		for (label j = posI; j < end; j++)
		{
			tokens[j] = tokens[j + 1];
		}

		tokens.setSize(tokens.size() - 1);
	}
	else if (varTokens.size() > 1)
	{
		tokens.setSize(tokens.size() + varTokens.size() - 1);

		label end = tokens.size() - 1;
		label offset = varTokens.size() - 1;

		for (label j = end; j > posI; j--)
		{
			tokens[j] = tokens[j - offset];
		}
	}

	forAll(varTokens, j)
	{
		tokens[posI + j] = varTokens[j];
	}
}


// ************************************************************************* //