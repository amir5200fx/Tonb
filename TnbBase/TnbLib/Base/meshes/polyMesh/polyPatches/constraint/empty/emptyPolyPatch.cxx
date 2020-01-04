#include <emptyPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(emptyPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, emptyPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, emptyPolyPatch, dictionary);
}

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::emptyPolyPatch::emptyPolyPatch
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


tnbLib::emptyPolyPatch::emptyPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(name, dict, index, bm)
{}


tnbLib::emptyPolyPatch::emptyPolyPatch
(
	const emptyPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm)
{}


tnbLib::emptyPolyPatch::emptyPolyPatch
(
	const emptyPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart)
{}


// ************************************************************************* //