#include <GAMGAgglomeration.hxx>

#include <lduMatrix.hxx>
#include <lduMesh.hxx>
#include <tnbTime.hxx>
#include <dlLibraryTable.hxx>
#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GAMGAgglomeration, 0);
	defineRunTimeSelectionTable(GAMGAgglomeration, lduMesh);
	defineRunTimeSelectionTable(GAMGAgglomeration, lduMatrix);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::GAMGAgglomeration::compactLevels(const label nCreatedLevels)
{
	nCells_.setSize(nCreatedLevels);
	restrictAddressing_.setSize(nCreatedLevels);
	meshLevels_.setSize(nCreatedLevels);
	interfaceLevels_.setSize(nCreatedLevels + 1);
}


bool tnbLib::GAMGAgglomeration::continueAgglomerating
(
	const label nCoarseCells
) const
{
	// Check the need for further agglomeration on all processors
	bool contAgg = nCoarseCells >= nCellsInCoarsestLevel_;
	reduce(contAgg, andOp<bool>());
	return contAgg;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::GAMGAgglomeration::GAMGAgglomeration
(
	const lduMesh& mesh,
	const dictionary& dict
)
	:
	MeshObject<lduMesh, GAMGAgglomeration>(mesh),

	maxLevels_(50),

	nCellsInCoarsestLevel_
	(
		readLabel(dict.lookup("nCellsInCoarsestLevel"))
	),

	nCells_(maxLevels_),
	restrictAddressing_(maxLevels_),
	faceRestrictAddressing_(maxLevels_),

	meshLevels_(maxLevels_),
	interfaceLevels_(maxLevels_ + 1)
{}


const tnbLib::GAMGAgglomeration& tnbLib::GAMGAgglomeration::New
(
	const lduMesh& mesh,
	const dictionary& dict
)
{
	if
		(
			!mesh.thisDb().foundObject<GAMGAgglomeration>
			(
				GAMGAgglomeration::typeName
				)
			)
	{
		word agglomeratorType(dict.lookup("agglomerator"));

		dlLibraryTable::open
		(
			dict,
			"geometricGAMGAgglomerationLibs",
			lduMeshConstructorTablePtr_
		);

		lduMeshConstructorTable::iterator cstrIter =
			lduMeshConstructorTablePtr_->find(agglomeratorType);

		if (cstrIter == lduMeshConstructorTablePtr_->end())
		{
			FatalErrorIn
			(
				"GAMGAgglomeration::New"
				"(const lduMesh& mesh, const dictionary& dict)"
			) << "Unknown GAMGAgglomeration type "
				<< agglomeratorType << ".\n"
				<< "Valid algebraic GAMGAgglomeration types are :"
				<< lduMatrixConstructorTablePtr_->sortedToc() << endl
				<< "Valid algebraic GAMGAgglomeration types are :"
				<< lduMeshConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return store(cstrIter()(mesh, dict).ptr());
	}
	else
	{
		return mesh.thisDb().lookupObject<GAMGAgglomeration>
			(
				GAMGAgglomeration::typeName
				);
	}
}


const tnbLib::GAMGAgglomeration& tnbLib::GAMGAgglomeration::New
(
	const lduMatrix& matrix,
	const dictionary& dict
)
{
	const lduMesh& mesh = matrix.mesh();

	if
		(
			!mesh.thisDb().foundObject<GAMGAgglomeration>
			(
				GAMGAgglomeration::typeName
				)
			)
	{
		word agglomeratorType(dict.lookup("agglomerator"));

		dlLibraryTable::open
		(
			dict,
			"algebraicGAMGAgglomerationLibs",
			lduMatrixConstructorTablePtr_
		);

		if
			(
				!lduMatrixConstructorTablePtr_
				|| !lduMatrixConstructorTablePtr_->found(agglomeratorType)
				)
		{
			return New(mesh, dict);
		}
		else
		{
			lduMatrixConstructorTable::iterator cstrIter =
				lduMatrixConstructorTablePtr_->find(agglomeratorType);

			return store(cstrIter()(matrix, dict).ptr());
		}
	}
	else
	{
		return mesh.thisDb().lookupObject<GAMGAgglomeration>
			(
				GAMGAgglomeration::typeName
				);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::GAMGAgglomeration::~GAMGAgglomeration()
{
	// Clear the interface storage by hand.
	// It is a list of ptrs not a PtrList for consistency of the interface
	for (label leveli = 1; leveli < interfaceLevels_.size(); leveli++)
	{
		lduInterfacePtrsList& curLevel = interfaceLevels_[leveli];

		forAll(curLevel, i)
		{
			if (curLevel.set(i))
			{
				delete curLevel(i);
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::lduMesh& tnbLib::GAMGAgglomeration::meshLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return mesh();
	}
	else
	{
		return meshLevels_[i - 1];
	}
}


const tnbLib::lduInterfacePtrsList& tnbLib::GAMGAgglomeration::interfaceLevel
(
	const label i
) const
{
	return interfaceLevels_[i];
}


// ************************************************************************* //