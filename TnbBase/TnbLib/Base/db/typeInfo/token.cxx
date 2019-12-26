#include <token.hxx>

#include <SortableList.hxx>
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::token::typeName = "token";
tnbLib::token tnbLib::token::undefinedToken;

defineTypeNameAndDebug(tnbLib::token::compound, 0);
defineRunTimeSelectionTable(tnbLib::token::compound, Istream);


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void tnbLib::token::parseError(const char* expected) const
{
	FatalIOError
		<< "Parse error, expected a " << expected
		<< ", found \n    " << info() << endl;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::token::compound::~compound()
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::token::compound> tnbLib::token::compound::New
(
	const word& compoundType,
	Istream& is
)
{
	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(compoundType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalErrorIn("token::compound::New(const word&, Istream&)")
			<< "Unknown compound type " << compoundType << nl << nl
			<< "Valid compound types:" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<tnbLib::token::compound>(cstrIter()(is));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::token::compound::isCompound(const word& name)
{
	return
		(
			IstreamConstructorTablePtr_
			&& IstreamConstructorTablePtr_->found(name)
			);
}


tnbLib::token::compound& tnbLib::token::transferCompoundToken()
{
	if (type_ == COMPOUND)
	{
		if (compoundTokenPtr_->empty())
		{
			FatalErrorIn("token::transferCompoundToken()")
				<< "compound has already been transfered from token\n    "
				<< info() << abort(FatalError);
		}
		else
		{
			compoundTokenPtr_->empty() = true;
		}

		return *compoundTokenPtr_;
	}
	else
	{
		parseError("compound");
		return *compoundTokenPtr_;
	}
}


// ************************************************************************* //