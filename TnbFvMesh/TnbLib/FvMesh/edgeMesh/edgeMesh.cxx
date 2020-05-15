#include <edgeMesh.hxx>

#include <mergePoints.hxx>
#include <StaticHashTable.hxx>
#include <dynamicLabelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::edgeMesh::calcPointEdges() const
{
	if (pointEdgesPtr_.valid())
	{
		FatalErrorIn("edgeMesh::calcPointEdges() const")
			<< "pointEdges already calculated." << abort(FatalError);
	}

	pointEdgesPtr_.reset(new labelListList(points_.size()));
	labelListList& pointEdges = pointEdgesPtr_();

	// Count
	labelList nEdgesPerPoint(points_.size(), 0);

	forAll(edges_, edgeI)
	{
		const edge& e = edges_[edgeI];

		nEdgesPerPoint[e[0]]++;
		nEdgesPerPoint[e[1]]++;
	}

	// Size
	forAll(pointEdges, pointI)
	{
		pointEdges[pointI].setSize(nEdgesPerPoint[pointI]);
	}

	// Fill
	nEdgesPerPoint = 0;

	forAll(edges_, edgeI)
	{
		const edge& e = edges_[edgeI];

		label p0 = e[0];
		pointEdges[p0][nEdgesPerPoint[p0]++] = edgeI;
		label p1 = e[1];
		pointEdges[p1][nEdgesPerPoint[p1]++] = edgeI;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// construct from components
tnbLib::edgeMesh::edgeMesh(const pointField& points, const edgeList& edges)
	:
	points_(points),
	edges_(edges)
{}


// construct as copy
tnbLib::edgeMesh::edgeMesh(const edgeMesh& em)
	:
	points_(em.points_),
	edges_(em.edges_),
	pointEdgesPtr_(NULL)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::edgeMesh::regions(labelList& edgeRegion) const
{
	edgeRegion.setSize(edges_.size());
	edgeRegion = -1;

	label startEdgeI = 0;

	label currentRegion = 0;

	while (true)
	{
		while (startEdgeI < edges_.size() && edgeRegion[startEdgeI] != -1)
		{
			startEdgeI++;
		}

		if (startEdgeI == edges_.size())
		{
			break;
		}

		// Found edge that has not yet been assigned a region.
		// Mark connected region with currentRegion starting at startEdgeI.

		edgeRegion[startEdgeI] = currentRegion;
		labelList edgesToVisit(1, startEdgeI);

		while (edgesToVisit.size())
		{
			// neighbours of current edgesToVisit
			dynamicLabelList newEdgesToVisit(edgesToVisit.size());

			// Mark all point connected edges with current region.
			forAll(edgesToVisit, i)
			{
				label edgeI = edgesToVisit[i];

				// Mark connected edges
				const edge& e = edges_[edgeI];

				forAll(e, fp)
				{
					const labelList& pEdges = pointEdges()[e[fp]];

					forAll(pEdges, pEdgeI)
					{
						label nbrEdgeI = pEdges[pEdgeI];

						if (edgeRegion[nbrEdgeI] == -1)
						{
							edgeRegion[nbrEdgeI] = currentRegion;
							newEdgesToVisit.append(nbrEdgeI);
						}
					}
				}
			}

			edgesToVisit.transfer(newEdgesToVisit);
		}

		currentRegion++;
	}
	return currentRegion;
}


void tnbLib::edgeMesh::mergePoints(const scalar mergeDist)
{
	pointField newPoints;
	labelList pointMap;

	bool hasMerged = tnbLib::mergePoints
	(
		points_,
		mergeDist,
		false,
		pointMap,
		newPoints,
		vector::zero
	);

	if (hasMerged)
	{
		pointEdgesPtr_.clear();

		points_.transfer(newPoints);

		// Renumber and make sure e[0] < e[1] (not really nessecary)
		forAll(edges_, edgeI)
		{
			edge& e = edges_[edgeI];

			label p0 = pointMap[e[0]];
			label p1 = pointMap[e[1]];

			if (p0 < p1)
			{
				e[0] = p0;
				e[1] = p1;
			}
			else
			{
				e[0] = p1;
				e[1] = p0;
			}
		}

		// Compact using a hashtable and commutative hash of edge.
		StaticHashTable<label, edge, Hash<edge> > edgeToLabel
		(
			2 * edges_.size()
		);

		label newEdgeI = 0;

		forAll(edges_, edgeI)
		{
			const edge& e = edges_[edgeI];

			if (e[0] != e[1])
			{
				if (edgeToLabel.insert(e, newEdgeI))
				{
					newEdgeI++;
				}
			}
		}

		edges_.setSize(newEdgeI);

		for
			(
				StaticHashTable<label, edge, Hash<edge> >::const_iterator iter =
				edgeToLabel.begin();
				iter != edgeToLabel.end();
				++iter
				)
		{
			edges_[iter()] = iter.key();
		}
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::edgeMesh::operator=(const edgeMesh& rhs)
{
	points_ = rhs.points_;
	edges_ = rhs.edges_;
	pointEdgesPtr_.reset(NULL);
}


// ************************************************************************* //