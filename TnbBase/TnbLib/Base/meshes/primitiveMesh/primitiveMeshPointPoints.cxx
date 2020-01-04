#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcPointPoints() const
{
	if (debug)
	{
		Pout << "primitiveMesh::calcPointPoints() : "
			<< "calculating pointPoints"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorIn("primitiveMesh::calcPointPoints()")
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate pointPoints
	// if the pointer is already set
	if (ppPtr_)
	{
		FatalErrorIn("primitiveMesh::calcPointPoints() const")
			<< "pointPoints already calculated"
			<< abort(FatalError);
	}
	else
	{
		const edgeList& e = edges();
		const labelListList& pe = pointEdges();

		ppPtr_ = new labelListList(pe.size());
		labelListList& pp = *ppPtr_;

		forAll(pe, pointI)
		{
			pp[pointI].setSize(pe[pointI].size());

			forAll(pe[pointI], ppi)
			{
				if (e[pe[pointI][ppi]].start() == pointI)
				{
					pp[pointI][ppi] = e[pe[pointI][ppi]].end();
				}
				else if (e[pe[pointI][ppi]].end() == pointI)
				{
					pp[pointI][ppi] = e[pe[pointI][ppi]].start();
				}
				else
				{
					FatalErrorIn("primitiveMesh::calcPointPoints() const")
						<< "something wrong with edges"
						<< abort(FatalError);
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::pointPoints() const
{
	if (!ppPtr_)
	{
		calcPointPoints();
	}

	return *ppPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointPoints
(
	const label pointI,
	dynamicLabelList& storage
) const
{
	if (hasPointPoints())
	{
		return pointPoints()[pointI];
	}
	else
	{
		const edgeList& edges = this->edges();
		const labelList& pEdges = pointEdges()[pointI];

		storage.clear();

		if (pEdges.size() > storage.capacity())
		{
			storage.setCapacity(pEdges.size());
		}

		forAll(pEdges, i)
		{
			storage.append(edges[pEdges[i]].otherVertex(pointI));
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointPoints
(
	const label pointI
) const
{
	return pointPoints(pointI, labels_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //