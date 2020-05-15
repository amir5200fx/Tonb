#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Destructors * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::pointField& tnbLib::edgeMesh::points() const
{
	return points_;
}


inline const tnbLib::edgeList& tnbLib::edgeMesh::edges() const
{
	return edges_;
}


inline const tnbLib::labelListList& tnbLib::edgeMesh::pointEdges() const
{
	if (pointEdgesPtr_.empty())
	{
		calcPointEdges();
	}
	return pointEdgesPtr_();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //