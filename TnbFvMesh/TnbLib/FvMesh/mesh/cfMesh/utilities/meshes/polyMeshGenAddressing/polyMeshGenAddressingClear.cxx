#include <polyMeshGenAddressing.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void polyMeshGenAddressing::printAllocated() const
	{
		Pout << "polyMeshGenAddressing allocated :" << endl;

		if (edgesPtr_)
		{
			Pout << "    Edges" << endl;
		}

		if (ccPtr_)
		{
			Pout << "    Cell-cells" << endl;
		}

		if (ecPtr_)
		{
			Pout << "    Edge-cells" << endl;
		}

		if (pcPtr_)
		{
			Pout << "    Point-cells" << endl;
		}

		if (efPtr_)
		{
			Pout << "    Edge-faces" << endl;
		}

		if (pfPtr_)
		{
			Pout << "    Point-faces" << endl;
		}

		if (cePtr_)
		{
			Pout << "    Cell-edges" << endl;
		}

		if (fePtr_)
		{
			Pout << "    Face-edges" << endl;
		}

		if (pePtr_)
		{
			Pout << "    Point-edges" << endl;
		}

		if (ppPtr_)
		{
			Pout << "    Point-point" << endl;
		}

		if (cpPtr_)
		{
			Pout << "    Cell-point" << endl;
		}

		// Geometry
		if (cellCentresPtr_)
		{
			Pout << "    Cell-centres" << endl;
		}

		if (faceCentresPtr_)
		{
			Pout << "    Face-centres" << endl;
		}

		if (cellVolumesPtr_)
		{
			Pout << "    Cell-volumes" << endl;
		}

		if (faceAreasPtr_)
		{
			Pout << "    Face-areas" << endl;
		}
	}

	void polyMeshGenAddressing::clearGeom()
	{
		if (debug)
		{
			Pout << "polyMeshGenAddressing::clearGeom() : "
				<< "clearing geometric data"
				<< endl;
		}

		deleteDemandDrivenData(cellCentresPtr_);
		deleteDemandDrivenData(faceCentresPtr_);
		deleteDemandDrivenData(cellVolumesPtr_);
		deleteDemandDrivenData(faceAreasPtr_);
	}

	void polyMeshGenAddressing::clearAddressing()
	{
		if (debug)
		{
			Pout << "polyMeshGenAddressing::clearAddressing() : "
				<< "clearing topology"
				<< endl;
		}

		clearOutEdges();

		deleteDemandDrivenData(ccPtr_);
		deleteDemandDrivenData(ecPtr_);
		deleteDemandDrivenData(pcPtr_);

		deleteDemandDrivenData(efPtr_);
		deleteDemandDrivenData(pfPtr_);

		deleteDemandDrivenData(cePtr_);
		deleteDemandDrivenData(fePtr_);
		deleteDemandDrivenData(pePtr_);
		deleteDemandDrivenData(ppPtr_);
		deleteDemandDrivenData(cpPtr_);
	}

	void polyMeshGenAddressing::clearParallelAddressing()
	{
		deleteDemandDrivenData(globalPointLabelPtr_);
		deleteDemandDrivenData(globalFaceLabelPtr_);
		deleteDemandDrivenData(globalCellLabelPtr_);
		deleteDemandDrivenData(globalEdgeLabelPtr_);

		deleteDemandDrivenData(pProcsPtr_);
		deleteDemandDrivenData(globalToLocalPointAddressingPtr_);
		deleteDemandDrivenData(pointNeiProcsPtr_);
		deleteDemandDrivenData(eProcsPtr_);
		deleteDemandDrivenData(globalToLocalEdgeAddressingPtr_);
		deleteDemandDrivenData(edgeNeiProcsPtr_);
	}

	void polyMeshGenAddressing::clearOut()
	{
		clearGeom();
		clearAddressing();
		clearParallelAddressing();
	}


	void polyMeshGenAddressing::clearAll()
	{
		clearGeom();
		clearAddressing();
		clearParallelAddressing();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //