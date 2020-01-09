#include <treeBoundBox.hxx>

#include <ListOps.hxx>
#include <pointField.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::scalar tnbLib::treeBoundBox::great(GREAT);

const tnbLib::treeBoundBox tnbLib::treeBoundBox::greatBox
(
	vector(-GREAT, -GREAT, -GREAT),
	vector(GREAT, GREAT, GREAT)
);


const tnbLib::treeBoundBox tnbLib::treeBoundBox::invertedBox
(
	vector(GREAT, GREAT, GREAT),
	vector(-GREAT, -GREAT, -GREAT)
);


//! @cond - skip documentation : local scope only
const tnbLib::label facesArray[6][4] =
{
	{0, 4, 6, 2}, // left
	{1, 3, 7, 5}, // right
	{0, 1, 5, 4}, // bottom
	{2, 6, 7, 3}, // top
	{0, 2, 3, 1}, // back
	{4, 5, 7, 6}  // front
};
//! @endcond


const tnbLib::faceList tnbLib::treeBoundBox::faces
(
	initListList<face, label, 6, 4>(facesArray)
);


//! @cond - skip documentation : local scope only
const tnbLib::label edgesArray[12][2] =
{
	{0, 1}, // 0
	{1, 3},
	{2, 3}, // 2
	{0, 2},
	{4, 5}, // 4
	{5, 7},
	{6, 7}, // 6
	{4, 6},
	{0, 4}, // 8
	{1, 5},
	{3, 7}, // 10
	{2, 6}
};
//! @endcond


const tnbLib::edgeList tnbLib::treeBoundBox::edges
(
	initListList<edge, label, 12, 2>(edgesArray)
);


const tnbLib::FixedList<tnbLib::vector, 6> tnbLib::treeBoundBox::faceNormals
(
	calcFaceNormals()
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::FixedList<tnbLib::vector, 6> tnbLib::treeBoundBox::calcFaceNormals()
{
	FixedList<vector, 6> normals;
	normals[LEFT] = vector(-1, 0, 0);
	normals[RIGHT] = vector(1, 0, 0);
	normals[BOTTOM] = vector(0, -1, 0);
	normals[TOP] = vector(0, 1, 0);
	normals[BACK] = vector(0, 0, -1);
	normals[FRONT] = vector(0, 0, 1);
	return normals;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct as the bounding box of the given pointField
tnbLib::treeBoundBox::treeBoundBox(const UList<point>& points)
	:
	boundBox()
{
	if (points.empty())
	{
		WarningIn
		(
			"treeBoundBox::treeBoundBox(const UList<point>&)"
		) << "cannot find bounding box for zero-sized pointField"
			<< "returning zero" << endl;

		return;
	}

	this->min() = points[0];
	this->max() = points[0];

	for (label i = 1; i < points.size(); i++)
	{
		this->min() = ::tnbLib::min(this->min(), points[i]);
		this->max() = ::tnbLib::max(this->max(), points[i]);
	}
}


// Construct as the bounding box of the given pointField
tnbLib::treeBoundBox::treeBoundBox
(
	const UList<point>& points,
	const UList<label>& meshPoints
)
	:
	boundBox()
{
	if (points.empty() || meshPoints.empty())
	{
		WarningIn
		(
			"treeBoundBox::treeBoundBox"
			"(const UList<point>&, const UList<label>&)"
		) << "cannot find bounding box for zero-sized pointField"
			<< "returning zero" << endl;

		return;
	}

	min() = points[meshPoints[0]];
	max() = points[meshPoints[0]];

	for (label i = 1; i < meshPoints.size(); i++)
	{
		min() = ::tnbLib::min(min(), points[meshPoints[i]]);
		max() = ::tnbLib::max(max(), points[meshPoints[i]]);
	}
}


// Construct from Istream
tnbLib::treeBoundBox::treeBoundBox(Istream& is)
	:
	boundBox(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

//tnbLib::pointField tnbLib::treeBoundBox::points() const
//{
//	pointField points(8);
//	forAll(points, octant)
//	{
//		points[octant] = corner(octant);
//
//	}
//	return points;
//}


tnbLib::treeBoundBox tnbLib::treeBoundBox::subBbox(const direction octant) const
{
	return subBbox(midpoint(), octant);
}


// Octant to bounding box using permutation only.
tnbLib::treeBoundBox tnbLib::treeBoundBox::subBbox
(
	const point& mid,
	const direction octant
) const
{
	if (octant > 7)
	{
		FatalErrorIn
		(
			"treeBoundBox::subBbox(const point&, const direction)"
		) << "octant should be [0..7]"
			<< abort(FatalError);
	}

	// start with a copy of this bounding box and adjust limits accordingly
	treeBoundBox subBb(*this);
	point& bbMin = subBb.min();
	point& bbMax = subBb.max();

	if (octant & treeBoundBox::RIGHTHALF)
	{
		bbMin.x() = mid.x();    // mid -> max
	}
	else
	{
		bbMax.x() = mid.x();    // min -> mid
	}

	if (octant & treeBoundBox::TOPHALF)
	{
		bbMin.y() = mid.y();    // mid -> max
	}
	else
	{
		bbMax.y() = mid.y();    // min -> mid
	}

	if (octant & treeBoundBox::FRONTHALF)
	{
		bbMin.z() = mid.z();    // mid -> max
	}
	else
	{
		bbMax.z() = mid.z();    // min -> mid
	}

	return subBb;
}


bool tnbLib::treeBoundBox::overlaps
(
	const point& centre,
	const scalar radiusSqr
) const
{
	// Find out where centre is in relation to bb.
	// Find nearest point on bb.
	scalar distSqr = 0;

	for (direction dir = 0; dir < vector::nComponents; dir++)
	{
		scalar d0 = min()[dir] - centre[dir];
		scalar d1 = max()[dir] - centre[dir];

		if ((d0 > 0) != (d1 > 0))
		{
			// centre inside both extrema. This component does not add any
			// distance.
		}
		else if (tnbLib::mag(d0) < tnbLib::mag(d1))
		{
			distSqr += d0 * d0;
		}
		else
		{
			distSqr += d1 * d1;
		}

		if (distSqr > radiusSqr)
		{
			return false;
		}
	}

	return true;
}


// line intersection. Returns true if line (start to end) inside
// bb or intersects bb. Sets pt to intersection.
//
// Sutherlands algorithm:
//   loop
//     - start = intersection of line with one of the planes bounding
//       the bounding box
//     - stop if start inside bb (return true)
//     - stop if start and end in same 'half' (e.g. both above bb)
//       (return false)
//
// Uses posBits to efficiently determine 'half' in which start and end
// point are.
//
// Note:
//   - sets coordinate to exact position: e.g. pt.x() = min().x()
//     since plane intersect routine might have truncation error.
//     This makes sure that posBits tests 'inside'
bool tnbLib::treeBoundBox::intersects
(
	const point& overallStart,
	const vector& overallVec,
	const point& start,
	const point& end,
	point& pt,
	direction& ptOnFaces
) const
{
	const direction endBits = posBits(end);

	pt = start;

	// Note
	// Optimising compilers (Intel 12) reorganises the code in
	// a way which executes all divisions before doing the if-check.
	// This causes a floating point exception of division by zero.
	// Furthermore, division by VSMALL (first number larger than zero) may
	// in some cases cause floating point exception overflow, and stabilisation
	// is required.  Added by HJ, 21/Sep/2011

	scalar s;

	//HJ, experimental: problems with round-off on Intel 12 compiler.
	// HJ, 29/Sep/2011
	const scalar smallNumber = VSMALL;
	const scalar kSmall = 1000 * smallNumber;

	while (true)
	{
		direction ptBits = posBits(pt);

		if (ptBits == 0)
		{
			// pt inside bb
			ptOnFaces = faceBits(pt);

			return true;
		}

		if ((ptBits & endBits) != 0)
		{
			// pt and end in same block outside of bb
			ptOnFaces = faceBits(pt);

			return false;
		}

		if (ptBits & LEFTBIT)
		{
			// Intersect with plane V=min, n=-1,0,0
			if (tnbLib::mag(overallVec.x()) > kSmall)
			{
				s = (min().x() - overallStart.x()) /
					stabilise(overallVec.x(), smallNumber);

				pt.x() = min().x();
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				// Vector not in x-direction. But still intersecting bb planes.
				// So must be close - just snap to bb.
				pt.x() = min().x();
			}
		}
		else if (ptBits & RIGHTBIT)
		{
			// Intersect with plane V=max, n=1,0,0
			if (tnbLib::mag(overallVec.x()) > kSmall)
			{
				s = (max().x() - overallStart.x()) /
					stabilise(overallVec.x(), smallNumber);

				pt.x() = max().x();
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				pt.x() = max().x();
			}
		}
		else if (ptBits & BOTTOMBIT)
		{
			// Intersect with plane V=min, n=0,-1,0
			if (tnbLib::mag(overallVec.y()) > kSmall)
			{
				s = (min().y() - overallStart.y()) /
					stabilise(overallVec.y(), smallNumber);

				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = min().y();
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				pt.x() = min().y();
			}
		}
		else if (ptBits & TOPBIT)
		{
			// Intersect with plane V=max, n=0,1,0
			if (tnbLib::mag(overallVec.y()) > kSmall)
			{
				s = (max().y() - overallStart.y()) /
					stabilise(overallVec.y(), smallNumber);

				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = max().y();
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				pt.y() = max().y();
			}
		}
		else if (ptBits & BACKBIT)
		{
			// Intersect with plane V=min, n=0,0,-1
			if (tnbLib::mag(overallVec.z()) > kSmall)
			{
				s = (min().z() - overallStart.z()) /
					stabilise(overallVec.z(), smallNumber);

				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = min().z();
			}
			else
			{
				pt.z() = min().z();
			}
		}
		else if (ptBits & FRONTBIT)
		{
			// Intersect with plane V=max, n=0,0,1
			if (tnbLib::mag(overallVec.z()) > kSmall)
			{
				s = (max().z() - overallStart.z()) /
					stabilise(overallVec.z(), smallNumber);

				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = max().z();
			}
			else
			{
				pt.z() = max().z();
			}
		}
	}
}


bool tnbLib::treeBoundBox::intersects
(
	const point& start,
	const point& end,
	point& pt
) const
{
	direction ptBits;

	return intersects(start, end - start, start, end, pt, ptBits);
}


// this.bb fully contains bb
bool tnbLib::treeBoundBox::contains(const treeBoundBox& bb) const
{
	return contains(bb.min()) && contains(bb.max());
}


bool tnbLib::treeBoundBox::contains(const vector& dir, const point& pt) const
{
	//
	// Compare all components against min and max of bb
	//
	for (direction cmpt = 0; cmpt < 3; cmpt++)
	{
		if (pt[cmpt] < min()[cmpt])
		{
			return false;
		}
		else if (pt[cmpt] == min()[cmpt])
		{
			// On edge. Outside if direction points outwards.
			if (dir[cmpt] < 0)
			{
				return false;
			}
		}

		if (pt[cmpt] > max()[cmpt])
		{
			return false;
		}
		else if (pt[cmpt] == max()[cmpt])
		{
			// On edge. Outside if direction points outwards.
			if (dir[cmpt] > 0)
			{
				return false;
			}
		}
	}

	// All components inside bb
	return true;
}


// Code position of pt on bounding box faces
tnbLib::direction tnbLib::treeBoundBox::faceBits(const point& pt) const
{
	direction faceBits = 0;

	if (pt.x() == min().x())
	{
		faceBits |= LEFTBIT;
	}
	else if (pt.x() == max().x())
	{
		faceBits |= RIGHTBIT;
	}

	if (pt.y() == min().y())
	{
		faceBits |= BOTTOMBIT;
	}
	else if (pt.y() == max().y())
	{
		faceBits |= TOPBIT;
	}

	if (pt.z() == min().z())
	{
		faceBits |= BACKBIT;
	}
	else if (pt.z() == max().z())
	{
		faceBits |= FRONTBIT;
	}

	return faceBits;
}


// Code position of point relative to box
tnbLib::direction tnbLib::treeBoundBox::posBits(const point& pt) const
{
	direction posBits = 0;

	if (pt.x() < min().x())
	{
		posBits |= LEFTBIT;
	}
	else if (pt.x() > max().x())
	{
		posBits |= RIGHTBIT;
	}

	if (pt.y() < min().y())
	{
		posBits |= BOTTOMBIT;
	}
	else if (pt.y() > max().y())
	{
		posBits |= TOPBIT;
	}

	if (pt.z() < min().z())
	{
		posBits |= BACKBIT;
	}
	else if (pt.z() > max().z())
	{
		posBits |= FRONTBIT;
	}

	return posBits;
}


// nearest and furthest corner coordinate.
// !names of treeBoundBox::min() and treeBoundBox::max() are confusing!
void tnbLib::treeBoundBox::calcExtremities
(
	const point& pt,
	point& nearest,
	point& furthest
) const
{
	scalar nearX, nearY, nearZ;
	scalar farX, farY, farZ;

	if (tnbLib::mag(min().x() - pt.x()) < tnbLib::mag(max().x() - pt.x()))
	{
		nearX = min().x();
		farX = max().x();
	}
	else
	{
		nearX = max().x();
		farX = min().x();
	}

	if (tnbLib::mag(min().y() - pt.y()) < tnbLib::mag(max().y() - pt.y()))
	{
		nearY = min().y();
		farY = max().y();
	}
	else
	{
		nearY = max().y();
		farY = min().y();
	}

	if (tnbLib::mag(min().z() - pt.z()) < tnbLib::mag(max().z() - pt.z()))
	{
		nearZ = min().z();
		farZ = max().z();
	}
	else
	{
		nearZ = max().z();
		farZ = min().z();
	}

	nearest = point(nearX, nearY, nearZ);
	furthest = point(farX, farY, farZ);
}


tnbLib::scalar tnbLib::treeBoundBox::maxDist(const point& pt) const
{
	point near, far;
	calcExtremities(pt, near, far);

	return tnbLib::mag(far - pt);
}


// Distance comparator
// Compare all vertices of bounding box against all of other bounding
// box to see if all vertices of one are nearer
tnbLib::label tnbLib::treeBoundBox::distanceCmp
(
	const point& pt,
	const treeBoundBox& other
) const
{
	//
	// Distance point <-> nearest and furthest away vertex of this
	//

	point nearThis, farThis;

	// get nearest and furthest away vertex
	calcExtremities(pt, nearThis, farThis);

	const scalar minDistThis =
		sqr(nearThis.x() - pt.x())
		+ sqr(nearThis.y() - pt.y())
		+ sqr(nearThis.z() - pt.z());
	const scalar maxDistThis =
		sqr(farThis.x() - pt.x())
		+ sqr(farThis.y() - pt.y())
		+ sqr(farThis.z() - pt.z());

	//
	// Distance point <-> other
	//

	point nearOther, farOther;

	// get nearest and furthest away vertex
	other.calcExtremities(pt, nearOther, farOther);

	const scalar minDistOther =
		sqr(nearOther.x() - pt.x())
		+ sqr(nearOther.y() - pt.y())
		+ sqr(nearOther.z() - pt.z());
	const scalar maxDistOther =
		sqr(farOther.x() - pt.x())
		+ sqr(farOther.y() - pt.y())
		+ sqr(farOther.z() - pt.z());

	//
	// Categorize
	//
	if (maxDistThis < minDistOther)
	{
		// All vertices of this are nearer to point than any vertex of other
		return -1;
	}
	else if (minDistThis > maxDistOther)
	{
		// All vertices of this are further from point than any vertex of other
		return 1;
	}
	else
	{
		// Mixed bag
		return 0;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

bool tnbLib::operator==(const treeBoundBox& a, const treeBoundBox& b)
{
	return operator==
		(
			static_cast<const boundBox&>(a),
			static_cast<const boundBox&>(b)
			);
}


bool tnbLib::operator!=(const treeBoundBox& a, const treeBoundBox& b)
{
	return !(a == b);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const treeBoundBox& bb)
{
	return os << static_cast<const boundBox&>(bb);
}


tnbLib::Istream& tnbLib::operator>>(Istream& is, treeBoundBox& bb)
{
	return is >> static_cast<boundBox&>(bb);
}


// ************************************************************************* //