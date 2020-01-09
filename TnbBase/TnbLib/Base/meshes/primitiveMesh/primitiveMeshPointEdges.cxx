#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void primitiveMesh::calcPointEdges() const
	{
		// Loop through edges and mark up points

		if (debug)
		{
			Pout << "primitiveMesh::calcPointEdges() : "
				<< "calculating pointEdges"
				<< endl;
		}

		// It is an error to attempt to recalculate pointEdges
		// if the pointer is already set
		if (pePtr_)
		{
			FatalErrorIn("primitiveMesh::calcPointEdges() const")
				<< "pointEdges already calculated"
				<< abort(FatalError);
		}
		else
		{
			const edgeList& e = edges();

			// Count edges per point

			labelList npe(nPoints(), 0);

			forAll(e, edgeI)
			{
				npe[e[edgeI].start()]++;
				npe[e[edgeI].end()]++;
			}


			// Size and fill edges per point

			pePtr_ = new labelListList(npe.size());
			labelListList& pointEdgeAddr = *pePtr_;

			forAll(pointEdgeAddr, pointI)
			{
				pointEdgeAddr[pointI].setSize(npe[pointI]);
			}
			npe = 0;

			forAll(e, edgeI)
			{
				label v0 = e[edgeI].start();

				pointEdgeAddr[v0][npe[v0]++] = edgeI;

				label v1 = e[edgeI].end();

				pointEdgeAddr[v1][npe[v1]++] = edgeI;
			}
		}
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const labelListList& primitiveMesh::pointEdges() const
	{
		if (!pePtr_)
		{
			calcPointEdges();
		}

		return *pePtr_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //