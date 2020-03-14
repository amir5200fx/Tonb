#include <topoSetSource.hxx>

#include <polyMesh.hxx>
#include <topoSet.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(topoSetSource, 0);
	defineRunTimeSelectionTable(topoSetSource, word);
	defineRunTimeSelectionTable(topoSetSource, istream);

	// Construct named object from dictionary
	autoPtr<topoSetSource> topoSetSource::New
	(
		const word& topoSetSourceType,
		const polyMesh& mesh,
		const dictionary& dict
	)
	{
		wordConstructorTable::iterator cstrIter =
			wordConstructorTablePtr_
			->find(topoSetSourceType);

		if (cstrIter == wordConstructorTablePtr_->end())
		{
			FatalErrorIn
			(
				"topoSetSource::New(const word&, "
				"const polyMesh&, const dictionary&)"
			) << "Unknown topoSetSource type " << topoSetSourceType
				<< endl << endl
				<< "Valid topoSetSource types : " << endl
				<< wordConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<topoSetSource>(cstrIter()(mesh, dict));
	}


	// Construct named object from Istream
	autoPtr<topoSetSource> topoSetSource::New
	(
		const word& topoSetSourceType,
		const polyMesh& mesh,
		Istream& is
	)
	{
		istreamConstructorTable::iterator cstrIter =
			istreamConstructorTablePtr_
			->find(topoSetSourceType);

		if (cstrIter == istreamConstructorTablePtr_->end())
		{
			FatalErrorIn
			(
				"topoSetSource::New(const word&, "
				"const polyMesh&, Istream&)"
			) << "Unknown topoSetSource type " << topoSetSourceType
				<< endl << endl
				<< "Valid topoSetSource types : " << endl
				<< istreamConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<topoSetSource>(cstrIter()(mesh, is));
	}


} // End namespace tnbLib


tnbLib::HashTable<tnbLib::string>* tnbLib::topoSetSource::usageTablePtr_ = NULL;

template<>
const char* tnbLib::NamedEnum<tnbLib::topoSetSource::setAction, 8>::names[] =
{
	"clear",
	"new",
	"invert",
	"add",
	"delete",
	"subset",
	"list",
	"remove"
};


const tnbLib::NamedEnum<tnbLib::topoSetSource::setAction, 8>
tnbLib::topoSetSource::actionNames_;


const tnbLib::string tnbLib::topoSetSource::illegalSource_
(
	"Illegal topoSetSource name"
);


tnbLib::Istream& tnbLib::topoSetSource::checkIs(Istream& is)
{
	if (is.good() && !is.eof())
	{
		return is;
	}
	else
	{
		FatalErrorIn("cellToFace::cellToFace") << "Istream not good"
			<< exit(FatalError);

		return is;
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::topoSetSource::addOrDelete
(
	topoSet& set,
	const label cellI,
	const bool add
) const
{
	if (add)
	{
		set.insert(cellI);
	}
	else
	{
		set.erase(cellI);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::topoSetSource::topoSetSource(const polyMesh& mesh)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::topoSetSource::~topoSetSource()
{}


// ************************************************************************* //