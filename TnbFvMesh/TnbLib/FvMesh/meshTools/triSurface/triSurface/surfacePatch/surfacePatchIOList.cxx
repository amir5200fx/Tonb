#include <surfacePatchIOList.hxx>

#include <entry.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::surfacePatchIOList, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from IOObject
tnbLib::surfacePatchIOList::surfacePatchIOList
(
	const IOobject& io
)
	:
	surfacePatchList(),
	regIOobject(io)
{
	tnbLib::string functionName =
		"surfacePatchIOList::surfacePatchIOList"
		"(const IOobject& io)";


	if (readOpt() == IOobject::MUST_READ)
	{
		surfacePatchList& patches = *this;

		// read polyPatchList
		Istream& is = readStream(typeName);

		PtrList<entry> patchEntries(is);
		patches.setSize(patchEntries.size());

		label faceI = 0;

		forAll(patches, patchI)
		{
			const dictionary& dict = patchEntries[patchI].dict();

			label patchSize = readLabel(dict.lookup("nFaces"));
			label startFaceI = readLabel(dict.lookup("startFace"));

			patches[patchI] =
				surfacePatch
				(
					word(dict.lookup("geometricType")),
					patchEntries[patchI].keyword(),
					patchSize,
					startFaceI,
					patchI
				);


			if (startFaceI != faceI)
			{
				FatalErrorIn(functionName)
					<< "Patches are not ordered. Start of patch " << patchI
					<< " does not correspond to sum of preceding patches."
					<< endl
					<< "while reading " << io.objectPath()
					<< exit(FatalError);
			}

			faceI += patchSize;
		}

		// Check state of IOstream
		is.check(functionName.c_str());

		close();
	}
}

// Construct from IOObject
tnbLib::surfacePatchIOList::surfacePatchIOList
(
	const IOobject& io,
	const surfacePatchList& patches
)
	:
	surfacePatchList(patches),
	regIOobject(io)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfacePatchIOList::~surfacePatchIOList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// writeData member function required by regIOobject
bool tnbLib::surfacePatchIOList::writeData(Ostream& os) const
{
	os << *this;
	return os.good();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const surfacePatchIOList& patches)
{
	os << patches.size() << nl << token::BEGIN_LIST;

	forAll(patches, patchI)
	{
		patches[patchI].writeDict(os);
	}

	os << token::END_LIST;

	return os;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

// ************************************************************************* //