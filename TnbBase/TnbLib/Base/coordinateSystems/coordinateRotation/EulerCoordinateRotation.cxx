#include <EulerCoordinateRotation.hxx>

#include <Switch.hxx>
#include <mathematicalConstants.hxx>
#include <dictionary.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(EulerCoordinateRotation, 0);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		EulerCoordinateRotation,
		dictionary
	);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::EulerCoordinateRotation::calcTransform
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
				cos(phi)*cos(psi) - sin(phi)*sin(psi)*cos(theta),
				-sin(phi)*cos(psi)*cos(theta) - cos(phi)*sin(psi),
				sin(phi)*sin(theta),

				cos(phi)*sin(psi)*cos(theta) + sin(phi)*cos(psi),
				cos(phi)*cos(psi)*cos(theta) - sin(phi)*sin(psi),
				-cos(phi)*sin(theta),

				sin(psi)*sin(theta),
				cos(psi)*sin(theta),
				cos(theta)
			)
			);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::EulerCoordinateRotation::EulerCoordinateRotation()
	:
	coordinateRotation()
{}


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
(
	const vector& phiThetaPsi,
	const bool inDegrees
)
	:
	coordinateRotation()
{
	calcTransform
	(
		phiThetaPsi.component(vector::X),
		phiThetaPsi.component(vector::Y),
		phiThetaPsi.component(vector::Z),
		inDegrees
	);
}


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
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


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
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