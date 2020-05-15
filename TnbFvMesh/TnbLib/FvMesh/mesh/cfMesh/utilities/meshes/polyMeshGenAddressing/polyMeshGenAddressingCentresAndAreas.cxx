#include <polyMeshGenAddressing.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcFaceCentresAndAreas() const
	{
		if (faceCentresPtr_ || faceAreasPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcFaceCentresAndAreas() const")
				<< "Face centres or face areas already calculated"
				<< abort(FatalError);
		}

		const pointFieldPMG& points = mesh_.points();
		const faceListPMG& faces = mesh_.faces();

		faceCentresPtr_ = new vectorField(faces.size());
		vectorField& fCtrs = *faceCentresPtr_;

		faceAreasPtr_ = new vectorField(faces.size());
		vectorField& fAreas = *faceAreasPtr_;

		makeFaceCentresAndAreas(points, fCtrs, fAreas);
	}

	void polyMeshGenAddressing::makeFaceCentresAndAreas
	(
		const pointFieldPMG& p,
		vectorField& fCtrs,
		vectorField& fAreas
	) const
	{
		const faceListPMG& fs = mesh_.faces();
		const label nFaces = fs.size();

# ifdef USE_OMP
# pragma omp parallel for if( nFaces > 1000 )
# endif
		for (label faceI = 0; faceI < nFaces; ++faceI)
		{
			const face& f = fs[faceI];
			label nPoints = f.size();

			// If the face is a triangle, do a direct calculation for efficiency
			// and to avoid round-off error-related problems
			if (nPoints == 3)
			{
				fCtrs[faceI] = (1.0 / 3.0)*(p[f[0]] + p[f[1]] + p[f[2]]);
				fAreas[faceI] = 0.5*((p[f[1]] - p[f[0]]) ^ (p[f[2]] - p[f[0]]));
			}
			else
			{
				vector sumN = vector::zero;
				scalar sumA = 0.0;
				vector sumAc = vector::zero;

				point fCentre = p[f[0]];
				for (label pi = 1; pi < nPoints; ++pi)
				{
					fCentre += p[f[pi]];
				}

				fCentre /= nPoints;

				for (label pi = 0; pi < nPoints; ++pi)
				{
					const point& nextPoint = p[f.nextLabel(pi)];

					vector c = p[f[pi]] + nextPoint + fCentre;
					vector n = (nextPoint - p[f[pi]]) ^ (fCentre - p[f[pi]]);
					scalar a = mag(n);

					sumN += n;
					sumA += a;
					sumAc += a * c;
				}

				fCtrs[faceI] = (1.0 / 3.0)*sumAc / (sumA + VSMALL);
				fAreas[faceI] = 0.5*sumN;
			}
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const vectorField& polyMeshGenAddressing::faceCentres() const
	{
		if (!faceCentresPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const vectorField& polyMeshGenAddressing::faceCentres() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcFaceCentresAndAreas();
		}

		return *faceCentresPtr_;
	}

	const vectorField& polyMeshGenAddressing::faceAreas() const
	{
		if (!faceAreasPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const vectorField& polyMeshGenAddressing::faceAreas() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcFaceCentresAndAreas();
		}

		return *faceAreasPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //