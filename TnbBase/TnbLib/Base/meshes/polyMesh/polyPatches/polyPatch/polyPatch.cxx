#include <polyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <polyBoundaryMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <SubField.hxx>
#include <entry.hxx>
#include <dictionary.hxx>
#include <pointPatchField.hxx>
#include <OFstream.hxx>
#include <demandDrivenData.hxx>
#include <faceList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(polyPatch, 0);

	debug::debugSwitch
		polyPatch::disallowGenericPolyPatch
		(
			"disallowGenericPolyPatch",
			0
		);

	defineRunTimeSelectionTable(polyPatch, word);
	defineRunTimeSelectionTable(polyPatch, dictionary);

	addToRunTimeSelectionTable(polyPatch, polyPatch, word);
	addToRunTimeSelectionTable(polyPatch, polyPatch, dictionary);
}


const tnbLib::debug::tolerancesSwitch
tnbLib::polyPatch::matchTol_
(
	"patchFaceMatchTol",
	1e-3
);

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::polyPatch::movePoints(const pointField& p)
{
	primitivePatch::movePoints(p);
}

void tnbLib::polyPatch::updateMesh()
{
	clearAddressing();
}


// Is old face now in the current patch?
bool tnbLib::polyPatch::inPatch
(
	const labelList& oldToNew,
	const label oldFaceI
) const
{
	label faceI = oldToNew[oldFaceI];

	return faceI >= start() && faceI < start() + size();
}


void tnbLib::polyPatch::writeOBJ(Ostream& os, const point& pt)
{
	os << "v " << pt.x() << ' ' << pt.y() << ' ' << pt.z() << endl;
}


void tnbLib::polyPatch::writeOBJ
(
	Ostream& os,
	const pointField& points,
	const labelList& pointLabels
)
{
	forAll(pointLabels, i)
	{
		writeOBJ(os, points[pointLabels[i]]);
	}
}


// Write edge
void tnbLib::polyPatch::writeOBJ
(
	Ostream& os,
	const point& p0,
	const point& p1,
	label& vertI
)
{
	writeOBJ(os, p0);
	vertI++;

	writeOBJ(os, p1);
	vertI++;

	os << "l " << vertI - 1 << ' ' << vertI << nl;
}


// Write patch
void tnbLib::polyPatch::writeOBJ
(
	const fileName& fName,
	const faceList& faces,
	const pointField& points
)
{
	OFstream os(fName);

	Map<label> foamToObj(4 * faces.size());

	label vertI = 0;

	forAll(faces, i)
	{
		const face& f = faces[i];

		forAll(f, fp)
		{
			if (foamToObj.insert(f[fp], vertI))
			{
				writeOBJ(os, points[f[fp]]);
				vertI++;
			}
		}

		os << 'l';
		forAll(f, fp)
		{
			os << ' ' << foamToObj[f[fp]] + 1;
		}
		os << ' ' << foamToObj[f[0]] + 1 << nl;
	}
}


// Get face centre with specified points
// (can't use points() since might not be set yet in morphing; usually called
//  with mapPolyMesh.premotionPoints())
tnbLib::tmp<tnbLib::pointField> tnbLib::polyPatch::calcFaceCentres
(
	const faceList& faces,
	const pointField& points
)
{
	tmp<pointField> tctrs(new pointField(faces.size()));

	pointField& ctrs = tctrs();

	forAll(faces, faceI)
	{
		ctrs[faceI] = faces[faceI].centre(points);
	}

	return tctrs;
}


// Get coordinate of f[0] for every face
tnbLib::tmp<tnbLib::pointField> tnbLib::polyPatch::getAnchorPoints
(
	const faceList& faces,
	const pointField& points
)
{
	tmp<pointField> tanchors(new pointField(faces.size()));

	pointField& anchors = tanchors();

	forAll(faces, faceI)
	{
		anchors[faceI] = points[faces[faceI][0]];
	}

	return tanchors;
}


// Given list of starts of patches and a face label determine the patch.
tnbLib::label tnbLib::polyPatch::whichPatch
(
	const labelList& patchStarts,
	const label faceI
)
{
	forAll(patchStarts, patchI)
	{
		if (patchStarts[patchI] <= faceI)
		{
			if (patchI == patchStarts.size() - 1)
			{
				return patchI;
			}
			else if (patchStarts[patchI + 1] > faceI)
			{
				return patchI;
			}
		}
	}

	return -1;
}


// Get local typical dimension and tolerance from that. Currently max of
// distance from centre to any of the face points.
tnbLib::scalarField tnbLib::polyPatch::calcFaceTol
(
	const faceList& faces,
	const pointField& points,
	const pointField& faceCentres
)
{
	// Calculate typical distance per face
	scalarField tols(faces.size());

	forAll(faces, faceI)
	{
		const point& cc = faceCentres[faceI];

		const face& f = faces[faceI];

		scalar maxLen = -GREAT;

		forAll(f, fp)
		{
			maxLen = max(maxLen, mag(points[f[fp]] - cc));
		}

		tols[faceI] = matchTol_()*maxLen;
	}

	return tols;
}


tnbLib::label tnbLib::polyPatch::getRotation
(
	const pointField& points,
	const face& f,
	const point& anchor,
	const scalar tol
)
{
	label anchorFp = -1;
	scalar minDistSqr = GREAT;

	forAll(f, fp)
	{
		scalar distSqr = magSqr(anchor - points[f[fp]]);

		if (distSqr < minDistSqr)
		{
			minDistSqr = distSqr;
			anchorFp = fp;
		}
	}

	if (anchorFp == -1 || mag(minDistSqr) > tol)
	{
		return -1;
	}
	else
	{
		// Positive rotation
		return (f.size() - anchorFp) % f.size();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::polyPatch::polyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	patchIdentifier(name, index),
	primitivePatch
	(
		faceSubList(bm.mesh().allFaces(), size, start),
		bm.mesh().allPoints()
	),
	start_(start),
	boundaryMesh_(bm),
	faceCellsPtr_(NULL),
	mePtr_(NULL)
{}


tnbLib::polyPatch::polyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	patchIdentifier(name, dict, index),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().allFaces(),
			readLabel(dict.lookup("nFaces")),
			readLabel(dict.lookup("startFace"))
		),
		bm.mesh().allPoints()
	),
	start_(readLabel(dict.lookup("startFace"))),
	boundaryMesh_(bm),
	faceCellsPtr_(NULL),
	mePtr_(NULL)
{}


tnbLib::polyPatch::polyPatch
(
	const polyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	patchIdentifier(pp),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().allFaces(),
			pp.size(),
			pp.start()
		),
		bm.mesh().allPoints()
	),
	start_(pp.start()),
	boundaryMesh_(bm),
	faceCellsPtr_(NULL),
	mePtr_(NULL)
{}


tnbLib::polyPatch::polyPatch
(
	const polyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	patchIdentifier(pp, index),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().allFaces(),
			newSize,
			newStart
		),
		bm.mesh().allPoints()
	),
	start_(newStart),
	boundaryMesh_(bm),
	faceCellsPtr_(NULL),
	mePtr_(NULL)
{}


tnbLib::polyPatch::polyPatch(const polyPatch& p)
	:
	patchIdentifier(p),
	primitivePatch(p),
	start_(p.start_),
	boundaryMesh_(p.boundaryMesh_),
	faceCellsPtr_(NULL),
	mePtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::polyPatch::~polyPatch()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::polyPatch::constraintType(const word& pt)
{
	return pointPatchField<scalar>::PointPatchConstructorTablePtr_->found(pt);
}


tnbLib::wordList tnbLib::polyPatch::constraintTypes()
{
	wordList cTypes(dictionaryConstructorTablePtr_->size());

	label i = 0;

	for
		(
			dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->begin();
			cstrIter != dictionaryConstructorTablePtr_->end();
			++cstrIter
			)
	{
		if (constraintType(cstrIter.key()))
		{
			cTypes[i++] = cstrIter.key();
		}
	}

	cTypes.setSize(i);

	return cTypes;
}


const tnbLib::polyBoundaryMesh& tnbLib::polyPatch::boundaryMesh() const
{
	return boundaryMesh_;
}


const tnbLib::vectorField::subField tnbLib::polyPatch::faceCentres() const
{
	return patchSlice(boundaryMesh().mesh().faceCentres());
}


const tnbLib::vectorField::subField tnbLib::polyPatch::faceAreas() const
{
	return patchSlice(boundaryMesh().mesh().faceAreas());
}


// Return the patch face neighbour cell centres
tnbLib::tmp<tnbLib::vectorField> tnbLib::polyPatch::faceCellCentres() const
{
	tmp<vectorField> tcc(new vectorField(size()));
	vectorField& cc = tcc();

	// get reference to global cell centres
	const vectorField& gcc = boundaryMesh_.mesh().cellCentres();

	const unallocLabelList& faceCells = this->faceCells();

	forAll(faceCells, facei)
	{
		cc[facei] = gcc[faceCells[facei]];
	}

	return tcc;
}


const tnbLib::unallocLabelList& tnbLib::polyPatch::faceCells() const
{
	if (!faceCellsPtr_)
	{
		faceCellsPtr_ = new labelList::subList
		(
			patchSlice(boundaryMesh().mesh().faceOwner())
		);
	}

	return *faceCellsPtr_;
}


const tnbLib::labelList& tnbLib::polyPatch::meshEdges() const
{
	if (!mePtr_)
	{
		mePtr_ =
			new labelList
			(
				primitivePatch::meshEdges
				(
					boundaryMesh().mesh().edges(),
					boundaryMesh().mesh().cellEdges(),
					faceCells()
				)
			);

		// 1.6.x merge.  Reconsider.  HJ, 19/Aug/2010
//         mePtr_ =
//             new labelList
//             (
//                 primitivePatch::meshEdges
//                 (
//                     boundaryMesh().mesh().edges(),
//                     boundaryMesh().mesh().pointEdges()
//                 )
//             );
	}

	return *mePtr_;
}


void tnbLib::polyPatch::clearAddressing()
{
	// Missing base level clear-out  HJ, 1/Mar/2009
	primitivePatch::clearOut();

	deleteDemandDrivenData(faceCellsPtr_);
	deleteDemandDrivenData(mePtr_);
}


void tnbLib::polyPatch::write(Ostream& os) const
{
	os.writeKeyword("type") << type() << token::END_STATEMENT << nl;
	patchIdentifier::write(os);
	os.writeKeyword("nFaces") << size() << token::END_STATEMENT << nl;
	os.writeKeyword("startFace") << start() << token::END_STATEMENT << nl;
}


void tnbLib::polyPatch::initOrder(const primitivePatch&) const
{}


bool tnbLib::polyPatch::order
(
	const primitivePatch&,
	labelList& faceMap,
	labelList& rotation
) const
{
	// Nothing changed.
	return false;
}


void tnbLib::polyPatch::syncOrder() const
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::polyPatch::operator=(const polyPatch& p)
{
	clearAddressing();

	patchIdentifier::operator=(p);
	primitivePatch::operator=(p);
	start_ = p.start_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const polyPatch& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& os, const polyPatch& p");
	return os;
}


// ************************************************************************* //
