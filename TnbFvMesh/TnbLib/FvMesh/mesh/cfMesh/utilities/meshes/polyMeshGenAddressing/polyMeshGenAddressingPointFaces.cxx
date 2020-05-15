#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcPointFaces() const
	{
		if (pfPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcPointFaces()")
				<< "pointFaces already calculated"
				<< abort(FatalError);
		}
		else
		{
			const faceListPMG& faces = mesh_.faces();
			const label nPoints = mesh_.points().size();

			//- create the addressing
			pfPtr_ = new VRWGraph();
			VRWGraph& pointFaceAddr = *pfPtr_;

			VRWGraphSMPModifier(pointFaceAddr).reverseAddressing(faces);
			pointFaceAddr.setSize(nPoints);
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::pointFaces() const
	{
		if (!pfPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::pointFaces() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcPointFaces();
		}

		return *pfPtr_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //