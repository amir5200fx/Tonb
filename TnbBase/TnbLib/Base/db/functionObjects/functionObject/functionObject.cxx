#include <functionObject.hxx>

#include <dictionary.hxx>
#include <dlLibraryTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineRunTimeSelectionTable(tnbLib::functionObject, dictionary);

tnbLib::debug::debugSwitch
tnbLib::functionObject::debug
(
	"functionObject",
	0
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObject::functionObject(const word& name)
	: name_(name)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::functionObject> tnbLib::functionObject::New
(
	const word& name,
	const Time& t,
	const dictionary& functionDict
)
{
	word functionType(functionDict.lookup("type"));

	if (debug)
	{
		Info << "Selecting function " << functionType << endl;
	}

	dlLibraryTable::open
	(
		functionDict,
		"functionObjectLibs",
		dictionaryConstructorTablePtr_
	);

	if (!dictionaryConstructorTablePtr_)
	{
		FatalErrorIn
		(
			"functionObject::New"
			"(const word& name, const Time&, const dictionary&)"
		) << "Unknown function type "
			<< functionType << nl << nl
			<< "Table of functionObjects is empty" << endl
			<< exit(FatalError);
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(functionType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"functionObject::New"
			"(const word& name, const Time&, const dictionary&)"
		) << "Unknown function type "
			<< functionType << nl << nl
			<< "Valid functions are : " << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << endl
			<< exit(FatalError);
	}

	return autoPtr<functionObject>(cstrIter()(name, t, functionDict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObject::~functionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::functionObject::name() const
{
	return name_;
}


bool tnbLib::functionObject::end()
{
	return execute();
}


tnbLib::autoPtr<tnbLib::functionObject> tnbLib::functionObject::iNew::operator()
(
	const word& name,
	Istream& is
	) const
{
	dictionary dict(is);
	return functionObject::New(name, time_, dict);
}


// ************************************************************************* //