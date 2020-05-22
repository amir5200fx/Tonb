#include <cellDistFuncs.hxx>

#include <polyMesh.hxx>
#include <polyBoundaryMesh.hxx>


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::labelHashSet tnbLib::cellDistFuncs::getPatchIDs() const
{
	const polyBoundaryMesh& bMesh = mesh().boundaryMesh();

	labelHashSet patchIDs(bMesh.size());

	forAll(bMesh, patchI)
	{
		if (isA<Type>(bMesh[patchI]))
		{
			patchIDs.insert(patchI);
		}
	}
	return patchIDs;
}


// ************************************************************************* //