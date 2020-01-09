#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcFaceCentresAndAreas() const
{
	if (debug)
	{
		Pout << "primitiveMesh::calcFaceCentresAndAreas() : "
			<< "Calculating face centres and face areas"
			<< endl;
	}

	// It is an error to attempt to recalculate faceCentres
	// if the pointer is already set
	if (faceCentresPtr_ || faceAreasPtr_)
	{
		FatalErrorIn("primitiveMesh::calcFaceCentresAndAreas() const")
			<< "Face centres or face areas already calculated"
			<< abort(FatalError);
	}

	faceCentresPtr_ = new vectorField(nFaces());
	vectorField& fCtrs = *faceCentresPtr_;

	faceAreasPtr_ = new vectorField(nFaces());
	vectorField& fAreas = *faceAreasPtr_;

	makeFaceCentresAndAreas(points(), fCtrs, fAreas);

	if (debug)
	{
		Pout << "primitiveMesh::calcFaceCentresAndAreas() : "
			<< "Finished calculating face centres and face areas"
			<< endl;
	}
}


void tnbLib::primitiveMesh::makeFaceCentresAndAreas
(
	const pointField& p,
	vectorField& fCtrs,
	vectorField& fAreas
) const
{
	const faceList& fs = faces();

	forAll(fs, facei)
	{
		const labelList& f = fs[facei];
		label nPoints = f.size();

		// If the face is a triangle, do a direct calculation for efficiency
		// and to avoid round-off error-related problems
		if (nPoints == 3)
		{
			fCtrs[facei] = (1.0 / 3.0)*(p[f[0]] + p[f[1]] + p[f[2]]);
			fAreas[facei] = 0.5*((p[f[1]] - p[f[0]]) ^ (p[f[2]] - p[f[0]]));
		}
		else
		{
			vector sumN = vector::zero;
			scalar sumA = 0.0;
			vector sumAc = vector::zero;

			point fCentre = p[f[0]];
			for (label pi = 1; pi < nPoints; pi++)
			{
				fCentre += p[f[pi]];
			}

			fCentre /= nPoints;

			for (label pi = 0; pi < nPoints; pi++)
			{
				const point& nextPoint = p[f[(pi + 1) % nPoints]];

				vector c = p[f[pi]] + nextPoint + fCentre;
				vector n = (nextPoint - p[f[pi]]) ^ (fCentre - p[f[pi]]);
				scalar a = mag(n);

				sumN += n;
				sumA += a;
				sumAc += a * c;
			}

			fCtrs[facei] = (1.0 / 3.0)*sumAc / (sumA + VSMALL);
			fAreas[facei] = 0.5*sumN;
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::vectorField& tnbLib::primitiveMesh::faceCentres() const
{
	if (!faceCentresPtr_)
	{
		calcFaceCentresAndAreas();
	}

	return *faceCentresPtr_;
}


const tnbLib::vectorField& tnbLib::primitiveMesh::faceAreas() const
{
	if (!faceAreasPtr_)
	{
		calcFaceCentresAndAreas();
	}

	return *faceAreasPtr_;
}


// ************************************************************************* //