#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void triSurface::writeSMESH(const bool writeSorted, Ostream& os) const
	{
		const pointField& ps = points();

		// Write header
		os << "# tetgen .smesh file" << endl
			<< ps.size() << " 3" << endl;   // 3 dimensions

		// Write vertex coords
		forAll(ps, pointi)
		{
			os << pointi << ' '
				<< ps[pointi].x() << ' '
				<< ps[pointi].y() << ' '
				<< ps[pointi].z() << endl;
		}

		if (writeSorted)
		{
			labelList faceMap;

			surfacePatchList myPatches(calcPatches(faceMap));

			os << size() << " 1" << endl;   // 1 attribute: region number

			label faceIndex = 0;

			forAll(myPatches, patchI)
			{
				// Print all faces belonging to this patch

				for
					(
						label patchFaceI = 0;
						patchFaceI < myPatches[patchI].size();
						patchFaceI++
						)
				{
					const label faceI = faceMap[faceIndex++];

					os << "3 " // triangles
						<< operator[](faceI)[0] << ' '
						<< operator[](faceI)[1] << ' '
						<< operator[](faceI)[2] << ' '
						<< operator[](faceI).region()   // region number
						<< endl;
				}
			}

			os << '0' << endl      // holes
				<< '0' << endl;     // regions
		}
		else
		{
			os << size() << " 1" << endl;   // 1 attribute: region number

			forAll(*this, faceI)
			{
				os << "3 "
					<< operator[](faceI)[0] << ' '
					<< operator[](faceI)[1] << ' '
					<< operator[](faceI)[2] << ' '
					<< operator[](faceI).region()       // region number
					<< endl;
			}

			os << '0' << endl      // holes
				<< '0' << endl;     // regions
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //