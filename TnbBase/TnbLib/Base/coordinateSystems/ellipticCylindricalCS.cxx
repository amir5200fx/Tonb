#include <ellipticCylindricalCS.hxx>

#include <Switch.hxx>
#include <dictionary.hxx>
#include <mathematicalConstants.hxx>
#include <boundBox.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ellipticCylindricalCS, 0);
	addToRunTimeSelectionTable
	(
		coordinateSystem,
		ellipticCylindricalCS,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ellipticCylindricalCS::ellipticCylindricalCS(const bool inDegrees)
	:
	coordinateSystem(),
	a_(0),
	inDegrees_(inDegrees)
{}


tnbLib::ellipticCylindricalCS::ellipticCylindricalCS
(
	const coordinateSystem& cs,
	const bool inDegrees
)
	:
	coordinateSystem(cs),
	a_(0),
	inDegrees_(inDegrees)
{}


tnbLib::ellipticCylindricalCS::ellipticCylindricalCS
(
	const word& name,
	const coordinateSystem& cs,
	const bool inDegrees
)
	:
	coordinateSystem(name, cs),
	a_(0),
	inDegrees_(inDegrees)
{}


tnbLib::ellipticCylindricalCS::ellipticCylindricalCS
(
	const word& name,
	const point& origin,
	const coordinateRotation& cr,
	const scalar a,
	const bool inDegrees
)
	:
	coordinateSystem(name, origin, cr),
	a_(a),
	inDegrees_(inDegrees)
{}


tnbLib::ellipticCylindricalCS::ellipticCylindricalCS
(
	const word& name,
	const point& origin,
	const vector& axis,
	const vector& direction,
	const scalar a,
	const bool inDegrees
)
	:
	coordinateSystem(name, origin, axis, direction),
	a_(a),
	inDegrees_(inDegrees)
{}


tnbLib::ellipticCylindricalCS::ellipticCylindricalCS
(
	const word& name,
	const dictionary& dict
)
	:
	coordinateSystem(name, dict),
	a_(readScalar(dict.lookup("a"))),
	inDegrees_(dict.lookupOrDefault<Switch>("degrees", true))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::coordinateSystem::spanInfo
tnbLib::ellipticCylindricalCS::spanLimited() const
{
	spanInfo b(Pair<bool>(true, true));

	// Upper bound or r is unlimited
	b[0] = Pair<bool>(true, false);

	// z is unlimited
	b[2] = Pair<bool>(false, false);

	return b;
}


tnbLib::boundBox tnbLib::ellipticCylindricalCS::spanBounds() const
{
	return boundBox
	(
		vector
		(
			0,
			(inDegrees_ ? -180.0 : -mathematicalConstant::pi),
			-GREAT
		),
		vector
		(
			GREAT,
			(inDegrees_ ? 180.0 : mathematicalConstant::pi),
			GREAT
		)
	);
}


bool tnbLib::ellipticCylindricalCS::inDegrees() const
{
	return inDegrees_;
}


tnbLib::Switch& tnbLib::ellipticCylindricalCS::inDegrees()
{
	return inDegrees_;
}


tnbLib::vector tnbLib::ellipticCylindricalCS::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	// Notation: u = local.x() v = local.y() z = local.z();
	scalar theta =
		local.y()*(inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0);

	return coordinateSystem::localToGlobal
	(
		vector
		(
			a_*cosh(local.x())*cos(theta),
			a_*sinh(local.x())*sin(theta),
			local.z()
		),
		translate
	);
}

tnbLib::tmp<tnbLib::vectorField> tnbLib::ellipticCylindricalCS::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	scalarField theta =
		local.component(vector::Y)*
		(inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0);

	vectorField lc(local.size());
	lc.replace
	(
		vector::X,
		a_*cosh(local.component(vector::X))*cos(theta)
	);

	lc.replace
	(
		vector::Y,
		a_*sinh(local.component(vector::X))*sin(theta)
	);

	lc.replace
	(
		vector::Z,
		local.component(vector::Z)
	);

	return coordinateSystem::localToGlobal(lc, translate);
}


tnbLib::vector tnbLib::ellipticCylindricalCS::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	notImplemented
	(
		"ellipticCylindricalCS::globalToLocal(const vector&, bool) const"
	);

	return vector::zero;
}

tnbLib::tmp<tnbLib::vectorField> tnbLib::ellipticCylindricalCS::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	notImplemented
	(
		"ellipticCylindricalCS::globalToLocal(const vectorField&, bool) const"
	);

	return tmp<vectorField>(vectorField::null());
}


void tnbLib::ellipticCylindricalCS::write(Ostream& os) const
{
	coordinateSystem::write(os);
	os << " inDegrees: " << inDegrees() << endl;
}


void tnbLib::ellipticCylindricalCS::writeDict(Ostream& os, bool subDict) const
{
	if (subDict)
	{
		os << indent << nl
			<< indent << token::BEGIN_BLOCK << incrIndent << nl;
	}

	coordinateSystem::writeDict(os, false);
	os.writeKeyword("inDegrees") << inDegrees_ << token::END_STATEMENT << nl;

	if (subDict)
	{
		os << decrIndent << indent << token::END_BLOCK << endl;
	}
}


// ************************************************************************* //