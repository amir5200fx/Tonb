#include <fpmaMesh.hxx>

#include <IOmanip.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from polyMeshGen
	tnbLib::fpmaMesh::fpmaMesh(const polyMeshGen& mesh)
		:
		mesh_(mesh)
	{
	}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	tnbLib::fpmaMesh::~fpmaMesh()
	{}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void tnbLib::fpmaMesh::writePoints(tnbLib::OFstream& fpmaGeometryFile) const
	{
		fpmaGeometryFile << mesh_.points().size() << nl;
		const pointFieldPMG& points = mesh_.points();
		forAll(points, pointI)
		{
			const point& p = points[pointI];
			fpmaGeometryFile << p.x() << ' ' << p.y() << ' ' << p.z() << ' ';
		}

		fpmaGeometryFile << nl;
	}

	void fpmaMesh::writeCells(OFstream& fpmaGeometryFile) const
	{
		const cellListPMG& cells = mesh_.cells();

		fpmaGeometryFile << cells.size() << nl;
		forAll(cells, cellI)
		{
			const cell& c = cells[cellI];

			fpmaGeometryFile << c.size();
			forAll(c, fI)
				fpmaGeometryFile << ' ' << c[fI];
			fpmaGeometryFile << nl;
		}
	}

	void tnbLib::fpmaMesh::writeFaces(OFstream& fpmaGeometryFile) const
	{
		const faceListPMG& faces = mesh_.faces();
		fpmaGeometryFile << faces.size() << nl;
		forAll(faces, faceI)
		{
			const face& f = faces[faceI];

			fpmaGeometryFile << f.size();
			forAllReverse(f, pI)
				fpmaGeometryFile << ' ' << f[pI];
			fpmaGeometryFile << nl;
		}
	}

	void tnbLib::fpmaMesh::writeSubsets(tnbLib::OFstream& fpmaGeometryFile) const
	{
		//- write patches as face selections
		const PtrList<boundaryPatch>& patches = mesh_.boundaries();

		label nSubsets(0);

		nSubsets += patches.size();
		DynList<label> indices;
		mesh_.pointSubsetIndices(indices);
		nSubsets += indices.size();
		Info << "Mesh has " << indices.size() << " point subsets" << endl;
		mesh_.faceSubsetIndices(indices);
		nSubsets += indices.size();
		Info << "Mesh has " << indices.size() << " face subsets" << endl;
		mesh_.cellSubsetIndices(indices);
		nSubsets += indices.size();
		Info << "Mesh has " << indices.size() << " cell subsets" << endl;

		fpmaGeometryFile << nSubsets << nl;

		//- write patches as face selections
		forAll(patches, patchI)
		{
			label start = patches[patchI].patchStart();
			const label size = patches[patchI].patchSize();

			fpmaGeometryFile << patches[patchI].patchName() << nl;
			fpmaGeometryFile << 3 << nl;
			fpmaGeometryFile << size << nl;
			for (label i = 0; i < size; ++i)
				fpmaGeometryFile << start++ << ' ';
			fpmaGeometryFile << nl;
		}

		//- write node selections
		mesh_.pointSubsetIndices(indices);
		forAll(indices, indexI)
		{
			labelLongList nodesInSubset;
			mesh_.pointsInSubset(indices[indexI], nodesInSubset);

			fpmaGeometryFile << mesh_.pointSubsetName(indices[indexI]) << nl;
			fpmaGeometryFile << 1 << nl;
			fpmaGeometryFile << nodesInSubset.size() << nl;
			forAll(nodesInSubset, i)
				fpmaGeometryFile << nodesInSubset[i] << ' ';
			fpmaGeometryFile << nl;
		}

		//- write face selections
		mesh_.faceSubsetIndices(indices);
		forAll(indices, indexI)
		{
			labelLongList facesInSubset;
			mesh_.facesInSubset(indices[indexI], facesInSubset);

			fpmaGeometryFile << mesh_.faceSubsetName(indices[indexI]) << nl;
			fpmaGeometryFile << 3 << nl;
			fpmaGeometryFile << facesInSubset.size() << nl;
			forAll(facesInSubset, i)
				fpmaGeometryFile << facesInSubset[i] << ' ';
			fpmaGeometryFile << nl;
		}

		//- write cell selections
		mesh_.cellSubsetIndices(indices);
		forAll(indices, indexI)
		{
			labelLongList cellsInSubset;
			mesh_.cellsInSubset(indices[indexI], cellsInSubset);

			fpmaGeometryFile << mesh_.cellSubsetName(indices[indexI]) << nl;
			fpmaGeometryFile << 2 << nl;
			fpmaGeometryFile << cellsInSubset.size() << nl;
			forAll(cellsInSubset, i)
				fpmaGeometryFile << cellsInSubset[i] << ' ';
			fpmaGeometryFile << nl;
		}
	}


	void fpmaMesh::write(OFstream& fpmaGeometryFile) const
	{
		writePoints(fpmaGeometryFile);

		writeFaces(fpmaGeometryFile);

		writeCells(fpmaGeometryFile);

		writeSubsets(fpmaGeometryFile);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //