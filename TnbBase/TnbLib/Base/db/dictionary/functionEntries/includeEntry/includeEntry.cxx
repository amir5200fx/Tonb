#include <includeEntry.hxx>

#include <dictionary.hxx>
#include <IFstream.hxx>
#include <addToMemberFunctionSelectionTable.hxx>
#include <primitiveEntry.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::includeEntry::typeName
(
	tnbLib::functionEntries::includeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeEntry
tnbLib::debug::debugSwitch
tnbLib::functionEntries::includeEntry::debug
(
	"includeEntry",
	0
);

namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeEntry,
			execute,
			primitiveEntryIstream
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::fileName tnbLib::functionEntries::includeEntry::includeFileName
(
	Istream& is
)
{
	fileName fName(is);
	fName.expand();

	if (fName.size() && fName[0] != '/')
	{
		fName = fileName(is.name()).path() / fName;
	}

	return fName;
}


bool tnbLib::functionEntries::includeEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	IFstream fileStream(includeFileName(is));

	if (fileStream)
	{
		parentDict.read(fileStream);
		return true;
	}
	else
	{
		FatalIOErrorIn
		(
			"functionEntries::includeEntry::includeEntry"
			"(dictionary& parentDict,Istream& is)",
			is
		) << "Cannot open include file " << fileStream.name()
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}

bool tnbLib::functionEntries::includeEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	IFstream fileStream(includeFileName(is));

	if (fileStream)
	{
		entry.read(parentDict, fileStream);
		return true;
	}
	else
	{
		FatalIOErrorIn
		(
			"functionEntries::includeEntry::includeEntry"
			"(dictionary& parentDict, primitiveEntry& entry, Istream& is)",
			is
		) << "Cannot open include file " << fileStream.name()
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}

// ************************************************************************* //