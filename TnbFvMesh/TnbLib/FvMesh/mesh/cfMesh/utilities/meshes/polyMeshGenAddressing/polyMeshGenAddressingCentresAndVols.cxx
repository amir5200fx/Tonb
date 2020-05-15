#include <polyMeshGenAddressing.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcCellCentresAndVols() const
	{
		if (cellCentresPtr_ || cellVolumesPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcCellCentresAndVols() const")
				<< "Cell centres or cell volumes already calculated"
				<< abort(FatalError);
		}

		const cellListPMG& cells = mesh_.cells();

		// set the accumulated cell centre to zero vector
		cellCentresPtr_ = new vectorField(cells.size());
		vectorField& cellCtrs = *cellCentresPtr_;

		// Initialise cell volumes to 0
		cellVolumesPtr_ = new scalarField(cells.size());
		scalarField& cellVols = *cellVolumesPtr_;

		// Make centres and volumes
		makeCellCentresAndVols(faceCentres(), faceAreas(), cellCtrs, cellVols);
	}

	void polyMeshGenAddressing::makeCellCentresAndVols
	(
		const vectorField& fCtrs,
		const vectorField& fAreas,
		vectorField& cellCtrs,
		scalarField& cellVols
	) const
	{
		const labelList& own = mesh_.owner();
		const cellListPMG& cells = mesh_.cells();
		const label nCells = cells.size();

# ifdef USE_OMP
# pragma omp parallel for if( nCells > 1000 )
# endif
		for (label cellI = 0; cellI < nCells; ++cellI)
		{
			const cell& c = cells[cellI];

			//- approximate the centre first
			vector cEst(vector::zero);
			forAll(c, fI)
				cEst += fCtrs[c[fI]];

			cEst /= c.size();

			//- start evaluating the volume and the cell centre
			vector cellCentre(vector::zero);
			scalar cellVol(0.0);

			forAll(c, fI)
			{
				// Calculate 3*face-pyramid volume
				scalar pyr3Vol = (fAreas[c[fI]] & (fCtrs[c[fI]] - cEst));

				if (own[c[fI]] != cellI)
					pyr3Vol *= -1.0;

				pyr3Vol = tnbLib::max(pyr3Vol, VSMALL);

				// Calculate face-pyramid centre
				const vector pc = (3.0 / 4.0)*fCtrs[c[fI]] + (1.0 / 4.0)*cEst;

				// Accumulate volume-weighted face-pyramid centre
				cellCentre += pyr3Vol * pc;

				// Accumulate face-pyramid volume
				cellVol += pyr3Vol;
			}

			cellCtrs[cellI] = cellCentre / cellVol;
			cellVols[cellI] = cellVol / 3.0;
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const vectorField& polyMeshGenAddressing::cellCentres() const
	{
		if (!cellCentresPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const vectorField& polyMeshGenAddressing::cellCentres() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcCellCentresAndVols();
		}

		return *cellCentresPtr_;
	}

	const scalarField& polyMeshGenAddressing::cellVolumes() const
	{
		if (!cellVolumesPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const scalarField& polyMeshGenAddressing::cellVolumes() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcCellCentresAndVols();
		}

		return *cellVolumesPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //