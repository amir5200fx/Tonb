#include <parabolicCylindricalCS.hxx>

#include <dictionary.hxx>
#include <mathematicalConstants.hxx>
#include <boundBox.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(parabolicCylindricalCS, 0);
	addToRunTimeSelectionTable
	(
		coordinateSystem,
		parabolicCylindricalCS,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::parabolicCylindricalCS::parabolicCylindricalCS(const bool inDegrees)
	:
	coordinateSystem(),
	inDegrees_(inDegrees)
{}


tnbLib::parabolicCylindricalCS::parabolicCylindricalCS
(
	const word& name,
	const point& origin,
	const coordinateRotation& cr,
	const bool inDegrees
)
	:
	coordinateSystem(name, origin, cr),
	inDegrees_(inDegrees)
{}


tnbLib::parabolicCylindricalCS::parabolicCylindricalCS
(
	const word& name,
	const dictionary& dict
)
	:
	coordinateSystem(name, dict),
	inDegrees_(dict.lookupOrDefault<Switch>("degrees", true))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::coordinateSystem::spanInfo
tnbLib::parabolicCylindricalCS::spanLimited() const
{
	spanInfo b(Pair<bool>(true, true));

	// Upper bound or r is unlimited
	b[0] = Pair<bool>(true, false);

	// z is unlimited
	b[2] = Pair<bool>(false, false);

	return b;
}


tnbLib::boundBox tnbLib::parabolicCylindricalCS::spanBounds() const
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


bool tnbLib::parabolicCylindricalCS::inDegrees() const
{
	return inDegrees_;
}


tnbLib::Switch& tnbLib::parabolicCylindricalCS::inDegrees()
{
	return inDegrees_;
}


tnbLib::vector tnbLib::parabolicCylindricalCS::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	// Notation: u = local.x() v = local.y() z = local.z();
	if (local.y() < 0.0)
	{
		FatalErrorIn
		(
			"parabolicCylindricalCS::localToGlobal(const vector&, bool) const"
		)
			<< "parabolic cylindrical coordinates v < 0"
			<< abort(FatalError);
	}

	return coordinateSystem::localToGlobal
	(
		vector
		(
			0.5*(sqr(local.x()) - sqr(local.y())),
			local.x()*local.y(),
			local.z()
		),
		translate
	);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::parabolicCylindricalCS::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	if (min(local.component(vector::Y)) < 0.0)
	{
		FatalErrorIn
		(
			"parabolicCylindricalCS::localToGlobal"
			"(const vectorField&, bool) const"
		) << "parabolic cylindrical coordinates v < 0"
			<< abort(FatalError);
	}

	vectorField lc(local.size());
	lc.replace
	(
		vector::X,
		0.5*
		(
			sqr(local.component(vector::X))
			- sqr(local.component(vector::Y))
			)
	);

	lc.replace
	(
		vector::Y,
		local.component(vector::X) * local.component(vector::Y)
	);

	lc.replace
	(
		vector::Z,
		local.component(vector::Z)
	);

	return coordinateSystem::localToGlobal(lc, translate);
}


tnbLib::vector tnbLib::parabolicCylindricalCS::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	notImplemented
	(
		"parabolicCylindricalCS::globalToLocal(const vector&, bool) const"
	);

	return vector::zero;
}

tnbLib::tmp<tnbLib::vectorField> tnbLib::parabolicCylindricalCS::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	notImplemented
	(
		"parabolicCylindricalCS::globalToLocal(const vectorField&, bool) const"
	);

	return tmp<vectorField>(vectorField::null());
}


void tnbLib::parabolicCylindricalCS::write(Ostream& os) const
{
	coordinateSystem::write(os);
	os << " inDegrees: " << inDegrees() << endl;
}


void tnbLib::parabolicCylindricalCS::writeDict(Ostream& os, bool subDict) const
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