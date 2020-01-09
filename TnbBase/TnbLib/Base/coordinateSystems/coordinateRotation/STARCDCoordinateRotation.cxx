#include <STARCDCoordinateRotation.hxx>

#include <Switch.hxx>
#include <mathematicalConstants.hxx>
#include <dictionary.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(STARCDCoordinateRotation, 0);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		STARCDCoordinateRotation,
		dictionary
	);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::STARCDCoordinateRotation::calcTransform
(
	const scalar rotZ,
	const scalar rotX,
	const scalar rotY,
	const bool inDegrees
)
{
	scalar x = rotX;
	scalar y = rotY;
	scalar z = rotZ;

	if (inDegrees)
	{
		x *= mathematicalConstant::pi / 180.0;
		y *= mathematicalConstant::pi / 180.0;
		z *= mathematicalConstant::pi / 180.0;
	}

	tensor::operator=
		(
			tensor
			(
				cos(y)*cos(z) - sin(x)*sin(y)*sin(z),
				-cos(x)*sin(z),
				sin(x)*cos(y)*sin(z) + sin(y)*cos(z),

				cos(y)*sin(z) + sin(x)*sin(y)*cos(z),
				cos(x)*cos(z),
				sin(y)*sin(z) - sin(x)*cos(y)*cos(z),

				-cos(x)*sin(y),
				sin(x),
				cos(x)*cos(y)
			)
			);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation()
	:
	coordinateRotation()
{}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const vector& rotZrotXrotY,
	const bool inDegrees
)
	:
	coordinateRotation()
{
	calcTransform
	(
		rotZrotXrotY.component(vector::X),
		rotZrotXrotY.component(vector::Y),
		rotZrotXrotY.component(vector::Z),
		inDegrees
	);
}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const scalar rotZ,
	const scalar rotX,
	const scalar rotY,
	const bool inDegrees
)
	:
	coordinateRotation()
{
	calcTransform(rotZ, rotX, rotY, inDegrees);
}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const dictionary& dict
)
	:
	coordinateRotation()
{
	vector rotation(dict.lookup("rotation"));

	calcTransform
	(
		rotation.component(vector::X),
		rotation.component(vector::Y),
		rotation.component(vector::Z),
		dict.lookupOrDefault<Switch>("degrees", true)
	);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //