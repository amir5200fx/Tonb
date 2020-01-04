#include <genericPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(genericPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, genericPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, genericPolyPatch, dictionary);
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::genericPolyPatch::genericPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(name, size, start, index, bm)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(name, dict, index, bm),
	actualTypeName_(dict.lookup("type")),
	dict_(dict)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const genericPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm),
	actualTypeName_(pp.actualTypeName_),
	dict_(pp.dict_)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const genericPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart),
	actualTypeName_(pp.actualTypeName_),
	dict_(pp.dict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::genericPolyPatch::~genericPolyPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::genericPolyPatch::write(Ostream& os) const
{
	os.writeKeyword("type") << actualTypeName_ << token::END_STATEMENT << nl;
	patchIdentifier::write(os);
	os.writeKeyword("nFaces") << size() << token::END_STATEMENT << nl;
	os.writeKeyword("startFace") << start() << token::END_STATEMENT << nl;

	for
		(
			dictionary::const_iterator iter = dict_.begin();
			iter != dict_.end();
			++iter
			)
	{
		if
			(
				iter().keyword() != "type"
				&& iter().keyword() != "nFaces"
				&& iter().keyword() != "startFace"
				)
		{
			iter().write(os);
		}
	}
}


// ************************************************************************* //