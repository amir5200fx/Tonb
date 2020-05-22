#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2 if w2 nearer to pt.
inline bool tnbLib::wallPoint::update
(
	const point& pt,
	const wallPoint& w2,
	const scalar tol
)
{
	//Already done in calling algorithm
	//if (w2.origin() == origin_)
	//{
	//    // Shortcut. Same input so same distance.
	//    return false;
	//}

	scalar dist2 = magSqr(pt - w2.origin());

	if (!valid())
	{
		// current not yet set so use any value
		distSqr_ = dist2;
		origin_ = w2.origin();

		return true;
	}

	scalar diff = distSqr_ - dist2;

	if (diff < 0)
	{
		// already nearer to pt
		return false;
	}

	if ((diff < SMALL) || ((distSqr_ > SMALL) && (diff / distSqr_ < tol)))
	{
		// don't propagate small changes
		return false;
	}
	else
	{
		// update with new values
		distSqr_ = dist2;
		origin_ = w2.origin();

		return true;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::wallPoint::wallPoint()
	:
	origin_(greatPoint),
	distSqr_(GREAT)
{}


// Construct from origin, distance
inline tnbLib::wallPoint::wallPoint(const point& origin, const scalar distSqr)
	:
	origin_(origin), distSqr_(distSqr)
{}


// Construct as copy
inline tnbLib::wallPoint::wallPoint(const wallPoint& wpt)
	:
	origin_(wpt.origin()), distSqr_(wpt.distSqr())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::point& tnbLib::wallPoint::origin() const
{
	return origin_;
}


inline tnbLib::point& tnbLib::wallPoint::origin()
{
	return origin_;
}


inline tnbLib::scalar tnbLib::wallPoint::distSqr() const
{
	return distSqr_;
}


inline tnbLib::scalar& tnbLib::wallPoint::distSqr()
{
	return distSqr_;
}


inline bool tnbLib::wallPoint::valid() const
{
	return origin_ != greatPoint;
}


// Checks for cyclic faces
inline bool tnbLib::wallPoint::sameGeometry
(
	const polyMesh&,
	const wallPoint& w2,
	const scalar tol
)
const
{
	scalar diff = mag(distSqr() - w2.distSqr());

	if (diff < SMALL)
	{
		return true;
	}
	else
	{
		if ((distSqr() > SMALL) && ((diff / distSqr()) < tol))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


inline void tnbLib::wallPoint::leaveDomain
(
	const polyMesh&,
	const polyPatch&,
	const label,
	const point& faceCentre
)
{
	origin_ -= faceCentre;
}


inline void tnbLib::wallPoint::transform
(
	const polyMesh&,
	const tensor& rotTensor
)
{
	origin_ = tnbLib::transform(rotTensor, origin_);
}


// Update absolute geometric quantities. Note that distance (distSqr_)
// is not affected by leaving/entering domain.
inline void tnbLib::wallPoint::enterDomain
(
	const polyMesh&,
	const polyPatch&,
	const label,
	const point& faceCentre
)
{
	// back to absolute form
	origin_ += faceCentre;
}


// Update this with w2 if w2 nearer to pt.
inline bool tnbLib::wallPoint::updateCell
(
	const polyMesh& mesh,
	const label thisCellI,
	const label neighbourFaceI,
	const wallPoint& neighbourWallInfo,
	const scalar tol
)
{
	return
		update
		(
			mesh.cellCentres()[thisCellI],
			neighbourWallInfo,
			tol
		);
}


// Update this with w2 if w2 nearer to pt.
inline bool tnbLib::wallPoint::updateFace
(
	const polyMesh& mesh,
	const label thisFaceI,
	const label neighbourCellI,
	const wallPoint& neighbourWallInfo,
	const scalar tol
)
{
	return
		update
		(
			mesh.faceCentres()[thisFaceI],
			neighbourWallInfo,
			tol
		);
}

// Update this with w2 if w2 nearer to pt.
inline bool tnbLib::wallPoint::updateFace
(
	const polyMesh& mesh,
	const label thisFaceI,
	const wallPoint& neighbourWallInfo,
	const scalar tol
)
{
	return
		update
		(
			mesh.faceCentres()[thisFaceI],
			neighbourWallInfo,
			tol
		);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::wallPoint::operator==(const tnbLib::wallPoint& rhs) const
{
	return origin() == rhs.origin();
}


inline bool tnbLib::wallPoint::operator!=(const tnbLib::wallPoint& rhs) const
{
	return !(*this == rhs);
}


// ************************************************************************* //