#include <axisCoordinateRotation.hxx>

#include <Switch.hxx>
#include <mathematicalConstants.hxx>
#include <dictionary.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(axisCoordinateRotation, 0);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		axisCoordinateRotation,
		dictionary
	);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::axisCoordinateRotation::calcTransform
(
	const scalar phiAngle,
	const scalar thetaAngle,
	const scalar psiAngle,
	const bool inDegrees
)
{
	scalar phi = phiAngle;
	scalar theta = thetaAngle;
	scalar psi = psiAngle;

	if (inDegrees)
	{
		phi *= mathematicalConstant::pi / 180.0;
		theta *= mathematicalConstant::pi / 180.0;
		psi *= mathematicalConstant::pi / 180.0;
	}

	tensor::operator=
		(
			tensor
			(
				cos(theta)*cos(psi),
				sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi),
				cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi),

				cos(theta)*sin(psi),
				sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi),
				cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi),

				-sin(theta),
				sin(phi)*cos(theta),
				cos(phi)*cos(theta)
			)
			);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::axisCoordinateRotation::axisCoordinateRotation
(
	const scalar phiAngle,
	const scalar thetaAngle,
	const scalar psiAngle,
	const bool inDegrees
)
	:
	coordinateRotation()
{
	calcTransform(phiAngle, thetaAngle, psiAngle, inDegrees);
}


tnbLib::axisCoordinateRotation::axisCoordinateRotation
(
	const dictionary& dict
)
	:
	coordinateRotation()
{
	scalar phi = readScalar(dict.lookup("phi"));
	scalar theta = readScalar(dict.lookup("theta"));
	scalar psi = readScalar(dict.lookup("psi"));

	calcTransform
	(
		phi,
		theta,
		psi,
		dict.lookupOrDefault<Switch>("degrees", true)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
