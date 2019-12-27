#include <includeIfPresentEntry.hxx>

#include <dictionary.hxx>
#include <IFstream.hxx>
#include <addToMemberFunctionSelectionTable.hxx>
#include <primitiveEntry.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::includeIfPresentEntry::typeName
(
	tnbLib::functionEntries::includeIfPresentEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeIfPresentEntry
tnbLib::debug::debugSwitch
tnbLib::functionEntries::includeIfPresentEntry::debug
(
	"includeIfPresentEntry",
	0
);

namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeIfPresentEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeIfPresentEntry,
			execute,
			primitiveEntryIstream
		);
	}
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::includeIfPresentEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	IFstream ifs(includeFileName(is));

	if (ifs)
	{
		parentDict.read(ifs);
	}

	return true;
}


bool tnbLib::functionEntries::includeIfPresentEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	IFstream ifs(includeFileName(is));

	if (ifs)
	{
		entry.read(parentDict, ifs);
	}

	return true;
}

// ************************************************************************* //