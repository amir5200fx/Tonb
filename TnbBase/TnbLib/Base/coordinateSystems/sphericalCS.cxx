#include <sphericalCS.hxx>

#include <one.hxx>
#include <dictionary.hxx>
#include <mathematicalConstants.hxx>
#include <boundBox.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sphericalCS, 0);
	addToRunTimeSelectionTable(coordinateSystem, sphericalCS, dictionary);
	addToRunTimeSelectionTable(coordinateSystem, sphericalCS, origRotation);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sphericalCS::sphericalCS(const bool inDegrees)
	:
	coordinateSystem(),
	inDegrees_(inDegrees)
{}


tnbLib::sphericalCS::sphericalCS
(
	const coordinateSystem& cs,
	const bool inDegrees
)
	:
	coordinateSystem(cs),
	inDegrees_(inDegrees)
{}


tnbLib::sphericalCS::sphericalCS
(
	const word& name,
	const coordinateSystem& cs,
	const bool inDegrees
)
	:
	coordinateSystem(name, cs),
	inDegrees_(inDegrees)
{}


tnbLib::sphericalCS::sphericalCS
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


tnbLib::sphericalCS::sphericalCS
(
	const word& name,
	const point& origin,
	const vector& axis,
	const vector& dirn,
	const bool inDegrees
)
	:
	coordinateSystem(name, origin, axis, dirn),
	inDegrees_(inDegrees)
{}


tnbLib::sphericalCS::sphericalCS
(
	const word& name,
	const dictionary& dict
)
	:
	coordinateSystem(name, dict),
	inDegrees_(dict.lookupOrDefault<Switch>("degrees", true))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::coordinateSystem::spanInfo tnbLib::sphericalCS::spanLimited() const
{
	spanInfo b(Pair<bool>(true, true));

	// Upper bound or r is unlimited
	b[0] = Pair<bool>(true, false);

	return b;
}


tnbLib::boundBox tnbLib::sphericalCS::spanBounds() const
{
	return boundBox
	(
		vector
		(
			0,
			(inDegrees_ ? -180.0 : -mathematicalConstant::pi),
			(inDegrees_ ? -90.0 : -mathematicalConstant::pi / 2)
		),
		vector
		(
			GREAT,
			(inDegrees_ ? 180.0 : mathematicalConstant::pi),
			(inDegrees_ ? 90.0 : mathematicalConstant::pi / 2)
		)
	);
}


bool tnbLib::sphericalCS::inDegrees() const
{
	return inDegrees_;
}


tnbLib::Switch& tnbLib::sphericalCS::inDegrees()
{
	return inDegrees_;
}


tnbLib::vector tnbLib::sphericalCS::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	scalar r = local.x();
	const scalar theta
	(
		local.y()
		*(inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0)
	);
	const scalar phi
	(
		local.z()
		*(inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0)
	);

	return coordinateSystem::localToGlobal
	(
		vector(r*cos(theta)*sin(phi), r*sin(theta)*sin(phi), r*cos(phi)),
		translate
	);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sphericalCS::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	const scalarField r = local.component(vector::X);
	const scalarField theta
	(
		local.component(vector::Y)
		* (inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0)
	);
	const scalarField phi
	(
		local.component(vector::Z)
		* (inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0)
	);

	vectorField lc(local.size());
	lc.replace(vector::X, r*cos(theta)*sin(phi));
	lc.replace(vector::Y, r*sin(theta)*sin(phi));
	lc.replace(vector::Z, r*cos(phi));

	return coordinateSystem::localToGlobal(lc, translate);
}


tnbLib::vector tnbLib::sphericalCS::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	const vector lc = coordinateSystem::globalToLocal(global, translate);
	const scalar r = mag(lc);

	return vector
	(
		r,
		atan2
		(
			lc.y(), lc.x()
		) * (inDegrees_ ? 180.0 / mathematicalConstant::pi : 1.0),
		acos
		(
			lc.z() / (r + SMALL)
		) * (inDegrees_ ? 180.0 / mathematicalConstant::pi : 1.0)
	);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sphericalCS::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	const vectorField lc = coordinateSystem::globalToLocal(global, translate);
	const scalarField r = mag(lc);

	tmp<vectorField> tresult(new vectorField(lc.size()));
	vectorField& result = tresult();

	result.replace
	(
		vector::X, r

	);

	result.replace
	(
		vector::Y,
		atan2
		(
			lc.component(vector::Y),
			lc.component(vector::X)
		) * (inDegrees_ ? 180.0 / mathematicalConstant::pi : 1.0)
	);

	result.replace
	(
		vector::Z,
		acos
		(
			lc.component(vector::Z) / (r + SMALL)
		) * (inDegrees_ ? 180.0 / mathematicalConstant::pi : 1.0)
	);

	return tresult;
}


void tnbLib::sphericalCS::write(Ostream& os) const
{
	coordinateSystem::write(os);
	os << " inDegrees: " << inDegrees() << endl;
}


void tnbLib::sphericalCS::writeDict(Ostream& os, bool subDict) const
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