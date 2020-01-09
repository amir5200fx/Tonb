#include <cylindricalCS.hxx>

#include <dictionary.hxx>
#include <mathematicalConstants.hxx>
#include <boundBox.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cylindricalCS, 0);
	addToRunTimeSelectionTable(coordinateSystem, cylindricalCS, dictionary);
	addToRunTimeSelectionTable(coordinateSystem, cylindricalCS, origRotation);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cylindricalCS::cylindricalCS(const bool inDegrees)
	:
	coordinateSystem(),
	inDegrees_(inDegrees)
{}


tnbLib::cylindricalCS::cylindricalCS
(
	const coordinateSystem& cs,
	const bool inDegrees
)
	:
	coordinateSystem(cs),
	inDegrees_(inDegrees)
{}


tnbLib::cylindricalCS::cylindricalCS
(
	const word& name,
	const coordinateSystem& cs,
	const bool inDegrees
)
	:
	coordinateSystem(name, cs),
	inDegrees_(inDegrees)
{}


tnbLib::cylindricalCS::cylindricalCS
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


tnbLib::cylindricalCS::cylindricalCS
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


tnbLib::cylindricalCS::cylindricalCS
(
	const word& name,
	const dictionary& dict
)
	:
	coordinateSystem(name, dict),
	inDegrees_(dict.lookupOrDefault<Switch>("degrees", true))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::coordinateSystem::spanInfo tnbLib::cylindricalCS::spanLimited() const
{
	spanInfo b(Pair<bool>(true, true));

	// Upper bound or r is unlimited
	b[0] = Pair<bool>(true, false);

	// z is unlimited
	b[2] = Pair<bool>(false, false);

	return b;
}


tnbLib::boundBox tnbLib::cylindricalCS::spanBounds() const
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


bool tnbLib::cylindricalCS::inDegrees() const
{
	return inDegrees_;
}


tnbLib::Switch& tnbLib::cylindricalCS::inDegrees()
{
	return inDegrees_;
}


tnbLib::vector tnbLib::cylindricalCS::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	scalar theta
	(
		local.y() * (inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0)
	);

	return coordinateSystem::localToGlobal
	(
		vector(local.x()*cos(theta), local.x()*sin(theta), local.z()),
		translate
	);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cylindricalCS::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	scalarField theta =
		(
			local.component(vector::Y)
			* (inDegrees_ ? mathematicalConstant::pi / 180.0 : 1.0)
			);


	vectorField lc(local.size());
	lc.replace(vector::X, local.component(vector::X)*cos(theta));
	lc.replace(vector::Y, local.component(vector::X)*sin(theta));
	lc.replace(vector::Z, local.component(vector::Z));

	return coordinateSystem::localToGlobal(lc, translate);
}


tnbLib::vector tnbLib::cylindricalCS::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	const vector lc = coordinateSystem::globalToLocal(global, translate);

	return vector
	(
		sqrt(sqr(lc.x()) + sqr(lc.y())),
		atan2
		(
			lc.y(),
			lc.x()
		) * (inDegrees_ ? 180.0 / mathematicalConstant::pi : 1.0),
		lc.z()
	);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cylindricalCS::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	const vectorField lc =
		coordinateSystem::globalToLocal(global, translate);

	tmp<vectorField> tresult(new vectorField(lc.size()));
	vectorField& result = tresult();

	result.replace
	(
		vector::X,
		sqrt(sqr(lc.component(vector::X)) + sqr(lc.component(vector::Y)))
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

	result.replace(vector::Z, lc.component(vector::Z));

	return tresult;
}


void tnbLib::cylindricalCS::write(Ostream& os) const
{
	coordinateSystem::write(os);
	os << " inDegrees: " << inDegrees() << endl;
}


void tnbLib::cylindricalCS::writeDict(Ostream& os, bool subDict) const
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