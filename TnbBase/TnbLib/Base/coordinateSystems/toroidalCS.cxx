#include <toroidalCS.hxx>

#include <dictionary.hxx>
#include <mathematicalConstants.hxx>
#include <boundBox.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(toroidalCS, 0);
	addToRunTimeSelectionTable(coordinateSystem, toroidalCS, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


tnbLib::toroidalCS::toroidalCS
(
	const word& name,
	const point& origin,
	const coordinateRotation& cr,
	const scalar radius,
	const bool inDegrees
)
	:
	coordinateSystem(name, origin, cr),
	radius_(radius),
	inDegrees_(inDegrees)
{}


tnbLib::toroidalCS::toroidalCS
(
	const word& name,
	const dictionary& dict
)
	:
	coordinateSystem(name, dict),
	radius_(readScalar(dict.lookup("radius"))),
	inDegrees_(dict.lookupOrDefault<Switch>("degrees", true))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::coordinateSystem::spanInfo tnbLib::toroidalCS::spanLimited() const
{
	spanInfo b(Pair<bool>(true, true));

	// Upper bound or r is unlimited
	b[0] = Pair<bool>(true, false);

	return b;
}


tnbLib::boundBox tnbLib::toroidalCS::spanBounds() const
{
	return boundBox
	(
		vector
		(
			0,
			(inDegrees_ ? -180.0 : -mathematicalConstant::pi),
			(inDegrees_ ? -180.0 : -mathematicalConstant::pi)
		),
		vector
		(
			GREAT,
			(inDegrees_ ? 180.0 : mathematicalConstant::pi),
			(inDegrees_ ? 180.0 : mathematicalConstant::pi)
		)
	);
}


bool tnbLib::toroidalCS::inDegrees() const
{
	return inDegrees_;
}


tnbLib::Switch& tnbLib::toroidalCS::inDegrees()
{
	return inDegrees_;
}


tnbLib::vector tnbLib::toroidalCS::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	// Notation: r = local.x()
	scalar theta = local.y()*mathematicalConstant::pi / 180.0;
	scalar phi = local.z()*mathematicalConstant::pi / 180.0;

	scalar rprime = radius_ + local.x()*sin(phi);

	if ((local.x()*sin(phi)) > (radius_))
	{
		FatalErrorIn("toroidalCS::toGlobal(vector) const")
			<< "Badly defined toroidal coordinates"
			<< abort(FatalError);
	}

	return coordinateSystem::localToGlobal
	(
		vector(rprime*cos(theta), rprime*sin(theta), local.x()*cos(phi)),
		translate
	);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::toroidalCS::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	const scalarField r = local.component(vector::X);

	const scalarField theta =
		local.component(vector::Y)*mathematicalConstant::pi / 180.0;

	const scalarField phi =
		local.component(vector::Z)*mathematicalConstant::pi / 180.0;

	const scalarField rprime = radius_ + r * sin(phi);

	vectorField lc(local.size());
	lc.replace(vector::X, rprime*cos(theta));
	lc.replace(vector::Y, rprime*sin(theta));
	lc.replace(vector::Z, r*cos(phi));

	return coordinateSystem::localToGlobal(lc, translate);
}


tnbLib::vector tnbLib::toroidalCS::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	notImplemented
	(
		"toroidalCS::globalToLocal(const vector&, bool) const"
	);

	return vector::zero;
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::toroidalCS::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	notImplemented
	(
		"toroidalCS::globalToLocal(const vectorField&, bool) const"
	);

	return tmp<vectorField>(vectorField::null());
}


void tnbLib::toroidalCS::write(Ostream& os) const
{
	coordinateSystem::write(os);
	os << " radius: " << radius() << " inDegrees: " << inDegrees() << endl;
}


void tnbLib::toroidalCS::writeDict(Ostream& os, bool subDict) const
{
	if (subDict)
	{
		os << indent << nl
			<< indent << token::BEGIN_BLOCK << incrIndent << nl;
	}

	coordinateSystem::writeDict(os, false);
	os.writeKeyword("radius") << radius() << token::END_STATEMENT << nl;
	os.writeKeyword("inDegrees") << inDegrees_ << token::END_STATEMENT << nl;

	if (subDict)
	{
		os << decrIndent << indent << token::END_BLOCK << endl;
	}
}

