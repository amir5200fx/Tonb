#include <plane.hxx>

#include <tensor.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Calculate base point and unit normal vector from plane equation
void tnbLib::plane::calcPntAndVec(const scalarList& C)
{
	if (mag(C[0]) > VSMALL)
	{
		basePoint_ = vector((-C[3] / C[0]), 0, 0);
	}
	else
	{
		if (mag(C[1]) > VSMALL)
		{
			basePoint_ = vector(0, (-C[3] / C[1]), 0);
		}
		else
		{
			if (mag(C[2]) > VSMALL)
			{
				basePoint_ = vector(0, 0, (-C[3] / C[2]));
			}
			else
			{
				FatalErrorIn("void plane::calcPntAndVec(const scalarList&)")
					<< "At least one plane coefficient must have a value"
					<< abort(FatalError);
			}
		}
	}

	unitVector_ = vector(C[0], C[1], C[2]);
	scalar magUnitVector(mag(unitVector_));

	if (magUnitVector < VSMALL)
	{
		FatalErrorIn("void plane::calcPntAndVec(const scalarList&)")
			<< "Plane normal defined with zero length"
			<< abort(FatalError);
	}

	unitVector_ /= magUnitVector;
}


void tnbLib::plane::calcPntAndVec
(
	const point& point1,
	const point& point2,
	const point& point3
)
{
	basePoint_ = (point1 + point2 + point3) / 3;
	vector line12 = point1 - point2;
	vector line23 = point2 - point3;

	if
		(
			mag(line12) < VSMALL
			|| mag(line23) < VSMALL
			|| mag(point3 - point1) < VSMALL
			)
	{
		FatalErrorIn
		(
			"void plane::calcPntAndVec\n"
			"(\n"
			"    const point&,\n"
			"    const point&,\n"
			"    const point&\n"
			")\n"
		) << "Bad points." << abort(FatalError);
	}

	unitVector_ = line12 ^ line23;
	scalar magUnitVector(mag(unitVector_));

	if (magUnitVector < VSMALL)
	{
		FatalErrorIn
		(
			"void plane::calcPntAndVec\n"
			"(\n"
			"    const point&,\n"
			"    const point&,\n"
			"    const point&\n"
			")\n"
		) << "Plane normal defined with zero length"
			<< abort(FatalError);
	}

	unitVector_ /= magUnitVector;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from normal vector through the origin
tnbLib::plane::plane(const vector& normalVector)
	:
	unitVector_(normalVector),
	basePoint_(vector::zero)
{}


// Construct from point and normal vector
tnbLib::plane::plane(const point& basePoint, const vector& normalVector)
	:
	unitVector_(normalVector),
	basePoint_(basePoint)
{
	scalar magUnitVector(mag(unitVector_));

	if (magUnitVector > VSMALL)
	{
		unitVector_ /= magUnitVector;
	}
	else
	{
		FatalErrorIn("plane::plane(const point&, const vector&)")
			<< "plane normal has got zero length"
			<< abort(FatalError);
	}
}


// Construct from plane equation
tnbLib::plane::plane(const scalarList& C)
{
	calcPntAndVec(C);
}


// Construct from three points
tnbLib::plane::plane
(
	const point& a,
	const point& b,
	const point& c
)
{
	calcPntAndVec(a, b, c);
}


// Construct from dictionary
tnbLib::plane::plane(const dictionary& dict)
	:
	unitVector_(vector::zero),
	basePoint_(point::zero)
{
	word planeType(dict.lookup("planeType"));

	if (planeType == "planeEquation")
	{
		const dictionary& subDict = dict.subDict("planeEquationDict");
		scalarList C(4);

		C[0] = readScalar(subDict.lookup("a"));
		C[1] = readScalar(subDict.lookup("b"));
		C[2] = readScalar(subDict.lookup("c"));
		C[3] = readScalar(subDict.lookup("d"));

		calcPntAndVec(C);

	}
	else if (planeType == "embeddedPoints")
	{
		const dictionary& subDict = dict.subDict("embeddedPoints");

		point point1(subDict.lookup("point1"));
		point point2(subDict.lookup("point2"));
		point point3(subDict.lookup("point3"));

		calcPntAndVec(point1, point2, point3);
	}
	else if (planeType == "pointAndNormal")
	{
		const dictionary& subDict = dict.subDict("pointAndNormalDict");

		basePoint_ = subDict.lookup("basePoint");
		unitVector_ = subDict.lookup("normalVector");
		unitVector_ /= mag(unitVector_);
	}
	else
	{
		FatalIOErrorIn
		(
			"plane::plane(const dictionary&)",
			dict
		)
			<< "Invalid plane type: " << planeType << nl
			<< "Valid types are planeEquation, embeddedPoints "
			<< "and pointAndNormal"
			<< abort(FatalIOError);
	}
}


// Construct from Istream. Assumes point and normal vector.
tnbLib::plane::plane(Istream& is)
	:
	unitVector_(is),
	basePoint_(is)
{
	scalar magUnitVector(mag(unitVector_));

	if (magUnitVector > VSMALL)
	{
		unitVector_ /= magUnitVector;
	}
	else
	{
		FatalErrorIn("plane::plane(Istream& is)")
			<< "plane normal has got zero length"
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Return plane normal vector
const tnbLib::vector& tnbLib::plane::normal() const
{
	return unitVector_;
}


// Return plane base point
const tnbLib::point& tnbLib::plane::refPoint() const
{
	return basePoint_;
}


// Return coefficcients for plane equation: ax + by + cz + d = 0
tnbLib::scalarList tnbLib::plane::planeCoeffs() const
{
	scalarList C(4);

	scalar magX = mag(unitVector_.x());
	scalar magY = mag(unitVector_.y());
	scalar magZ = mag(unitVector_.z());

	if (magX > magY)
	{
		if (magX > magZ)
		{
			C[0] = 1;
			C[1] = unitVector_.y() / unitVector_.x();
			C[2] = unitVector_.z() / unitVector_.x();
		}
		else
		{
			C[0] = 0;
			C[1] = 0;
			C[2] = 1;
		}
	}
	else
	{
		if (magY > magZ)
		{
			C[0] = 0;
			C[1] = 1;
			C[2] = unitVector_.z() / unitVector_.y();
		}
		else
		{
			C[0] = 0;
			C[1] = 0;
			C[2] = 1;
		}
	}

	C[3] = -C[0] * basePoint_.x()
		- C[1] * basePoint_.y()
		- C[2] * basePoint_.z();

	return C;
}


// Return nearest point in the plane for the given point
tnbLib::point tnbLib::plane::nearestPoint(const point& p) const
{
	return p - unitVector_ * ((p - basePoint_) & unitVector_);
}


// Return distance from the given point to the plane
tnbLib::scalar tnbLib::plane::distance(const point& p) const
{
	return mag((p - basePoint_) & unitVector_);
}


// Cutting point for plane and line defined by origin and direction
tnbLib::scalar tnbLib::plane::normalIntersect
(
	const point& pnt0,
	const vector& dir
) const
{
	scalar denom = stabilise((dir & unitVector_), VSMALL);

	return ((basePoint_ - pnt0) & unitVector_) / denom;
}


// Cutting line of two planes
tnbLib::plane::ray tnbLib::plane::planeIntersect(const plane& plane2) const
{
	// Mathworld plane-plane intersection. Assume there is a point on the
	// intersection line with z=0 and solve the two plane equations
	// for that (now 2x2 equation in x and y)
	// Better: use either z=0 or x=0 or y=0.

	const vector& n1 = normal();
	const vector& n2 = plane2.normal();

	const point& p1 = refPoint();
	const point& p2 = plane2.refPoint();

	scalar n1p1 = n1 & p1;
	scalar n2p2 = n2 & p2;

	vector dir = n1 ^ n2;

	// Determine zeroed out direction (can be x,y or z) by looking at which
	// has the largest component in dir.
	scalar magX = mag(dir.x());
	scalar magY = mag(dir.y());
	scalar magZ = mag(dir.z());

	direction iZero, i1, i2;

	if (magX > magY)
	{
		if (magX > magZ)
		{
			iZero = 0;
			i1 = 1;
			i2 = 2;
		}
		else
		{
			iZero = 2;
			i1 = 0;
			i2 = 1;
		}
	}
	else
	{
		if (magY > magZ)
		{
			iZero = 1;
			i1 = 2;
			i2 = 0;
		}
		else
		{
			iZero = 2;
			i1 = 0;
			i2 = 1;
		}
	}

	vector pt;

	pt[iZero] = 0;
	pt[i1] = (n2[i2] * n1p1 - n1[i2] * n2p2) / (n1[i1] * n2[i2] - n2[i1] * n1[i2]);
	pt[i2] = (n2[i1] * n1p1 - n1[i1] * n2p2) / (n1[i2] * n2[i1] - n1[i1] * n2[i2]);

	return ray(pt, dir);
}


// Cutting point of three planes
tnbLib::point tnbLib::plane::planePlaneIntersect
(
	const plane& plane2,
	const plane& plane3
) const
{
	List<scalarList> pcs(3);
	pcs[0] = planeCoeffs();
	pcs[1] = plane2.planeCoeffs();
	pcs[2] = plane3.planeCoeffs();

	tensor a
	(
		pcs[0][0], pcs[0][1], pcs[0][2],
		pcs[1][0], pcs[1][1], pcs[1][2],
		pcs[2][0], pcs[2][1], pcs[2][2]
	);

	vector b(pcs[0][3], pcs[1][3], pcs[2][3]);

	return (inv(a) & (-b));
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

bool tnbLib::operator==(const plane& a, const plane& b)
{
	if (a.basePoint_ == b.basePoint_ && a.unitVector_ == b.unitVector_)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tnbLib::operator!=(const plane& a, const plane& b)
{
	return !(a == b);
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const plane& a)
{
	os << a.unitVector_ << token::SPACE << a.basePoint_;

	return os;
}


// ************************************************************************* //