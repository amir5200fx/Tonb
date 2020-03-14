#include <triSurface.hxx>

#include <IOmanip.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void triSurface::writeTRI(const bool writeSorted, Ostream& os) const
	{
		const pointField& ps = points();

		// Write as cloud of triangles

		labelList faceMap;

		surfacePatchList myPatches(calcPatches(faceMap));

		if (writeSorted)
		{
			label faceIndex = 0;

			forAll(myPatches, patchI)
			{
				for
					(
						label patchFaceI = 0;
						patchFaceI < myPatches[patchI].size();
						patchFaceI++
						)
				{
					const label faceI = faceMap[faceIndex++];

					const point& p1 = ps[operator[](faceI)[0]];
					const point& p2 = ps[operator[](faceI)[1]];
					const point& p3 = ps[operator[](faceI)[2]];

					os << p1.x() << token::SPACE
						<< p1.y() << token::SPACE
						<< p1.z() << token::SPACE

						<< p2.x() << token::SPACE
						<< p2.y() << token::SPACE
						<< p2.z() << token::SPACE

						<< p3.x() << token::SPACE
						<< p3.y() << token::SPACE
						<< p3.z() << token::SPACE

						<< "0x" << hex << operator[](faceI).region() << dec
						<< endl;
				}
			}
		}
		else
		{
			forAll(*this, faceI)
			{
				const point& p1 = ps[operator[](faceI)[0]];
				const point& p2 = ps[operator[](faceI)[1]];
				const point& p3 = ps[operator[](faceI)[2]];

				os << p1.x() << token::SPACE
					<< p1.y() << token::SPACE
					<< p1.z() << token::SPACE

					<< p2.x() << token::SPACE
					<< p2.y() << token::SPACE
					<< p2.z() << token::SPACE

					<< p3.x() << token::SPACE
					<< p3.y() << token::SPACE
					<< p3.z() << token::SPACE

					<< "0x" << hex << operator[](faceI).region() << dec
					<< endl;
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //