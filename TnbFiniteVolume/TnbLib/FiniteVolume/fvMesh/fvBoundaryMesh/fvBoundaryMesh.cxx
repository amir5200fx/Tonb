#include <fvBoundaryMesh.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void fvBoundaryMesh::addPatches(const polyBoundaryMesh& basicBdry)
	{
		setSize(basicBdry.size());

		// Set boundary patches
		fvPatchList& Patches = *this;

		forAll(Patches, patchI)
		{
			Patches.set(patchI, fvPatch::New(basicBdry[patchI], *this));
		}
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	fvBoundaryMesh::fvBoundaryMesh
	(
		const fvMesh& m
	)
		:
		fvPatchList(0),
		mesh_(m)
	{}


	fvBoundaryMesh::fvBoundaryMesh
	(
		const fvMesh& m,
		const polyBoundaryMesh& basicBdry
	)
		:
		fvPatchList(basicBdry.size()),
		mesh_(m)
	{
		addPatches(basicBdry);
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void fvBoundaryMesh::movePoints()
	{
		forAll(*this, patchi)
		{
			operator[](patchi).initMovePoints();
		}

		forAll(*this, patchi)
		{
			operator[](patchi).movePoints();
		}
	}


	lduInterfacePtrsList fvBoundaryMesh::interfaces() const
	{
		lduInterfacePtrsList interfaces(size());

		forAll(interfaces, patchi)
		{
			if (isA<lduInterface>(this->operator[](patchi)))
			{
				interfaces.set
				(
					patchi,
					&refCast<const lduInterface>(this->operator[](patchi))
				);
			}
		}

		return interfaces;
	}


	void fvBoundaryMesh::readUpdate(const polyBoundaryMesh& basicBdry)
	{
		clear();
		addPatches(basicBdry);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //