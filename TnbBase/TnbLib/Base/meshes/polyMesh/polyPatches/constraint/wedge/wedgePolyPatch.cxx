#include <wedgePolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <SubField.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(wedgePolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, wedgePolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, wedgePolyPatch, dictionary);
}

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void tnbLib::wedgePolyPatch::initTransforms()
{
	if (empty())
	{
		return;
	}

	const pointField& points = this->points();

	patchNormal_ = operator[](0).normal(points);
	patchNormal_ /= mag(patchNormal_);

	centreNormal_ =
		vector
		(
			sign(patchNormal_.x())*(max(mag(patchNormal_.x()), 0.5) - 0.5),
			sign(patchNormal_.y())*(max(mag(patchNormal_.y()), 0.5) - 0.5),
			sign(patchNormal_.z())*(max(mag(patchNormal_.z()), 0.5) - 0.5)
		);
	centreNormal_ /= mag(centreNormal_);

	if
		(
			mag(centreNormal_.x() + centreNormal_.y() + centreNormal_.z())
			< (1 - SMALL)
			)
	{
		FatalErrorIn
		(
			"wedgePolyPatch::wedgePolyPatch(const polyPatch&, "
			"const fvBoundaryMesh&)"
		) << "wedge " << name()
			<< " centre plane does not align with a coordinate plane by "
			<< 1
			- mag(centreNormal_.x() + centreNormal_.y() + centreNormal_.z())
			<< exit(FatalError);
	}

	axis_ = centreNormal_ ^ patchNormal_;
	scalar magAxis = mag(axis_);
	axis_ /= magAxis;

	if (magAxis < SMALL)
	{
		FatalErrorIn
		(
			"wedgePolyPatch::initTransforms()"
		) << "wedge " << name()
			<< " plane aligns with a coordinate plane." << nl
			<< "    The wedge plane should make a small angle (~2.5deg)"
			" with the coordinate plane" << nl
			<< "    and the the pair of wedge planes should be symmetric"
			<< " about the coordinate plane." << nl
			<< "    Normal of face " << 0 << " is " << patchNormal_
			<< " , implied coordinate plane direction is " << centreNormal_
			<< exit(FatalError);
	}

	faceT_ = rotationTensor(centreNormal_, patchNormal_);
	cellT_ = faceT_ & faceT_;
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(name, size, start, index, bm)
{
	initTransforms();
}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(name, dict, index, bm)
{
	initTransforms();
}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const wedgePolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm)
{
	initTransforms();
}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const wedgePolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart)
{
	initTransforms();
}


// ************************************************************************* //