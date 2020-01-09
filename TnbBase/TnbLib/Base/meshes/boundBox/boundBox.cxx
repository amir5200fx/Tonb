#include <boundBox.hxx>

#include <token.hxx>
#include <PstreamCombineReduceOps.hxx>
#include <PstreamReduceOps.hxx>
#include <tmp.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::scalar tnbLib::boundBox::great(VGREAT);

const tnbLib::boundBox tnbLib::boundBox::greatBox
(
	point(-VGREAT, -VGREAT, -VGREAT),
	point(VGREAT, VGREAT, VGREAT)
);


const tnbLib::boundBox tnbLib::boundBox::invertedBox
(
	point(VGREAT, VGREAT, VGREAT),
	point(-VGREAT, -VGREAT, -VGREAT)
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::boundBox::calculate(const pointField& points, const bool doReduce)
{
	if (points.empty())
	{
		min_ = point::zero;
		max_ = point::zero;

		if (doReduce && Pstream::parRun())
		{
			// Use values that get overwritten by reduce minOp, maxOp below
			min_ = point(VGREAT, VGREAT, VGREAT);
			max_ = point(-VGREAT, -VGREAT, -VGREAT);
		}
	}
	else
	{
		min_ = points[0];
		max_ = points[0];

		forAll(points, i)
		{
			min_ = ::tnbLib::min(min_, points[i]);
			max_ = ::tnbLib::max(max_, points[i]);
		}
	}

	// Reduce parallel information
	if (doReduce)
	{
		reduce(min_, minOp<point>());
		reduce(max_, maxOp<point>());
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boundBox::boundBox(const pointField& points, const bool doReduce)
	:
	min_(point::zero),
	max_(point::zero)
{
	calculate(points, doReduce);
}


tnbLib::boundBox::boundBox(const tmp<pointField>& points, const bool doReduce)
	:
	min_(point::zero),
	max_(point::zero)
{
	calculate(points(), doReduce);
	points.clear();
}


tnbLib::boundBox::boundBox(Istream& is)
{
	operator>>(is, *this);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const boundBox& bb)
{
	if (os.format() == IOstream::ASCII)
	{
		os << bb.min_ << token::SPACE << bb.max_;
	}
	else
	{
		os.write
		(
			reinterpret_cast<const char*>(&bb.min_),
			sizeof(boundBox)
		);
	}

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const boundBox&)");
	return os;
}


tnbLib::Istream& tnbLib::operator>>(Istream& is, boundBox& bb)
{
	if (is.format() == IOstream::ASCII)
	{
		return is >> bb.min_ >> bb.max_;
	}
	else
	{
		is.read
		(
			reinterpret_cast<char*>(&bb.min_),
			sizeof(boundBox)
		);
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, boundBox&)");
	return is;
}

// ************************************************************************* //