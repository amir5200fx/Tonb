#include <cellMapper.hxx>

#include <demandDrivenData.hxx>
#include <polyMesh.hxx>
#include <mapPolyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::cellMapper::calcAddressing() const
{
	if
		(
			directAddrPtr_
			|| interpolationAddrPtr_
			|| weightsPtr_
			|| insertedCellLabelsPtr_
			)
	{
		FatalErrorIn("void cellMapper::calcAddressing() const")
			<< "Addressing already calculated."
			<< abort(FatalError);
	}

	if (direct())
	{
		// Direct addressing, no weights

		directAddrPtr_ = new labelList(mpm_.cellMap());
		labelList& directAddr = *directAddrPtr_;

		// Not necessary to resize the list as there are no retired cells
		// directAddr.setSize(mesh_.nCells());

		insertedCellLabelsPtr_ = new labelList(mesh_.nCells());
		labelList& insertedCells = *insertedCellLabelsPtr_;

		label nInsertedCells = 0;

		forAll(directAddr, cellI)
		{
			if (directAddr[cellI] < 0)
			{
				// Found inserted cell
				directAddr[cellI] = 0;
				insertedCells[nInsertedCells] = cellI;
				nInsertedCells++;
			}
		}

		insertedCells.setSize(nInsertedCells);
	}
	else
	{
		// Interpolative addressing

		interpolationAddrPtr_ = new labelListList(mesh_.nCells());
		labelListList& addr = *interpolationAddrPtr_;

		weightsPtr_ = new scalarListList(mesh_.nCells());
		scalarListList& w = *weightsPtr_;

		const List<objectMap>& cfp = mpm_.cellsFromPointsMap();

		forAll(cfp, cfpI)
		{
			// Get addressing
			const labelList& mo = cfp[cfpI].masterObjects();

			label cellI = cfp[cfpI].index();

			if (addr[cellI].size())
			{
				FatalErrorIn("void cellMapper::calcAddressing() const")
					<< "Master cell " << cellI
					<< " mapped from point cells " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[cellI] = mo;
			w[cellI] = scalarList(mo.size(), 1.0 / mo.size());
		}

		const List<objectMap>& cfe = mpm_.cellsFromEdgesMap();

		forAll(cfe, cfeI)
		{
			// Get addressing
			const labelList& mo = cfe[cfeI].masterObjects();

			label cellI = cfe[cfeI].index();

			if (addr[cellI].size())
			{
				FatalErrorIn("void cellMapper::calcAddressing() const")
					<< "Master cell " << cellI
					<< " mapped from edge cells " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[cellI] = mo;
			w[cellI] = scalarList(mo.size(), 1.0 / mo.size());
		}

		const List<objectMap>& cff = mpm_.cellsFromFacesMap();

		forAll(cff, cffI)
		{
			// Get addressing
			const labelList& mo = cff[cffI].masterObjects();

			label cellI = cff[cffI].index();

			if (addr[cellI].size())
			{
				FatalErrorIn("void cellMapper::calcAddressing() const")
					<< "Master cell " << cellI
					<< " mapped from face cells " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[cellI] = mo;
			w[cellI] = scalarList(mo.size(), 1.0 / mo.size());
		}

		const List<objectMap>& cfc = mpm_.cellsFromCellsMap();

		forAll(cfc, cfcI)
		{
			// Get addressing
			const labelList& mo = cfc[cfcI].masterObjects();

			label cellI = cfc[cfcI].index();

			if (addr[cellI].size())
			{
				FatalErrorIn("void cellMapper::calcAddressing() const")
					<< "Master cell " << cellI
					<< " mapped from cell cells " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[cellI] = mo;
			w[cellI] = scalarList(mo.size(), 1.0 / mo.size());
		}


		// Do mapped faces. Note that can already be set from cellsFromCells
		// so check if addressing size still zero.

		const labelList& cm = mpm_.cellMap();

		forAll(cm, cellI)
		{
			if (cm[cellI] > -1 && addr[cellI].empty())
			{
				// Mapped from a single cell
				addr[cellI] = labelList(1, cm[cellI]);
				w[cellI] = scalarList(1, 1.0);
			}
		}

		// Grab inserted points (for them the size of addressing is still zero)

		insertedCellLabelsPtr_ = new labelList(mesh_.nCells());
		labelList& insertedCells = *insertedCellLabelsPtr_;

		label nInsertedCells = 0;

		forAll(addr, cellI)
		{
			if (addr[cellI].empty())
			{
				// Mapped from a dummy cell
				addr[cellI] = labelList(1, 0);
				w[cellI] = scalarList(1, 1.0);

				insertedCells[nInsertedCells] = cellI;
				nInsertedCells++;
			}
		}

		insertedCells.setSize(nInsertedCells);
	}
}


void tnbLib::cellMapper::clearOut()
{
	deleteDemandDrivenData(directAddrPtr_);
	deleteDemandDrivenData(interpolationAddrPtr_);
	deleteDemandDrivenData(weightsPtr_);
	deleteDemandDrivenData(insertedCellLabelsPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::cellMapper::cellMapper(const mapPolyMesh& mpm)
	:
	mesh_(mpm.mesh()),
	mpm_(mpm),
	insertedCells_(true),
	direct_(false),
	directAddrPtr_(NULL),
	interpolationAddrPtr_(NULL),
	weightsPtr_(NULL),
	insertedCellLabelsPtr_(NULL)
{
	// Check for possibility of direct mapping
	if
		(
			mpm_.cellsFromPointsMap().empty()
			&& mpm_.cellsFromEdgesMap().empty()
			&& mpm_.cellsFromFacesMap().empty()
			&& mpm_.cellsFromCellsMap().empty()
			)
	{
		direct_ = true;
	}
	else
	{
		direct_ = false;
	}

	// Check for inserted cells
	// HJ, different criterion in faces: this is due to the fact that
	// I can retire faces but cannot retire cells
	// HJ, 5/Sep/2007
	if (direct_ && (mpm_.cellMap().size() == 0 || min(mpm_.cellMap()) > -1))
	{
		insertedCells_ = false;
	}
	else
	{
		// Need to check all 3 lists to see if there are inserted cells
		// with no owner

		// Make a copy of the cell map, add the entried for cells from points,
		// cells from edges and cells from faces and check for left-overs
		labelList cm(mesh_.nCells(), -1);

		const List<objectMap>& cfp = mpm_.cellsFromPointsMap();

		forAll(cfp, cfpI)
		{
			cm[cfp[cfpI].index()] = 0;
		}

		const List<objectMap>& cfe = mpm_.cellsFromEdgesMap();

		forAll(cfe, cfeI)
		{
			cm[cfe[cfeI].index()] = 0;
		}

		const List<objectMap>& cff = mpm_.cellsFromFacesMap();

		forAll(cff, cffI)
		{
			cm[cff[cffI].index()] = 0;
		}

		const List<objectMap>& cfc = mpm_.cellsFromCellsMap();

		forAll(cfc, cfcI)
		{
			cm[cfc[cfcI].index()] = 0;
		}

		if (min(cm) < 0)
		{
			insertedCells_ = true;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellMapper::~cellMapper()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::cellMapper::size() const
{
	return mpm_.cellMap().size();
}


tnbLib::label tnbLib::cellMapper::sizeBeforeMapping() const
{
	return mpm_.nOldCells();
}


const tnbLib::unallocLabelList& tnbLib::cellMapper::directAddressing() const
{
	if (!direct())
	{
		FatalErrorIn
		(
			"const unallocLabelList& cellMapper::directAddressing() const"
		) << "Requested direct addressing for an interpolative mapper."
			<< abort(FatalError);
	}

	if (!insertedObjects())
	{
		// No inserted cells.  Re-use cellMap
		return mpm_.cellMap();
	}
	else
	{
		if (!directAddrPtr_)
		{
			calcAddressing();
		}

		return *directAddrPtr_;
	}
}


const tnbLib::labelListList& tnbLib::cellMapper::addressing() const
{
	if (direct())
	{
		FatalErrorIn
		(
			"const labelListList& cellMapper::addressing() const"
		) << "Requested interpolative addressing for a direct mapper."
			<< abort(FatalError);
	}

	if (!interpolationAddrPtr_)
	{
		calcAddressing();
	}

	return *interpolationAddrPtr_;
}


const tnbLib::scalarListList& tnbLib::cellMapper::weights() const
{
	if (direct())
	{
		FatalErrorIn
		(
			"const scalarListList& cellMapper::weights() const"
		) << "Requested interpolative weights for a direct mapper."
			<< abort(FatalError);
	}

	if (!weightsPtr_)
	{
		calcAddressing();
	}

	return *weightsPtr_;
}


const tnbLib::labelList& tnbLib::cellMapper::insertedObjectLabels() const
{
	if (!insertedCellLabelsPtr_)
	{
		if (!insertedObjects())
		{
			// There are no inserted cells
			insertedCellLabelsPtr_ = new labelList(0);
		}
		else
		{
			calcAddressing();
		}
	}

	return *insertedCellLabelsPtr_;
}


// ************************************************************************* //