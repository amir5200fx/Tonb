#include <basicThermo.hxx>

#include <fvMesh.hxx>
#include <HashTable.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <fixedEnthalpyFvPatchScalarField.hxx>
#include <gradientInternalEnergyFvPatchScalarField.hxx>
#include <mixedEnthalpyFvPatchScalarField.hxx>
#include <fixedInternalEnergyFvPatchScalarField.hxx>
#include <gradientInternalEnergyFvPatchScalarField.hxx>
#include <mixedInternalEnergyFvPatchScalarField.hxx>
#include <gradientEnthalpyFvPatchScalarField.hxx>
#include <tnbTime.hxx>

/* * * * * * * * * * * * * * Private Static Data * * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(basicThermo, 0);
}

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::wordList tnbLib::basicThermo::hBoundaryTypes()
{
	const volScalarField::GeometricBoundaryField& tbf = T_.boundaryField();

	wordList hbt = tbf.types();

	forAll(tbf, patchi)
	{
		if (isA<fixedValueFvPatchScalarField>(tbf[patchi]))
		{
			hbt[patchi] = fixedEnthalpyFvPatchScalarField::typeName;
		}
		else if
			(
				isA<zeroGradientFvPatchScalarField>(tbf[patchi])
				|| isA<fixedGradientFvPatchScalarField>(tbf[patchi])
				)
		{
			hbt[patchi] = gradientEnthalpyFvPatchScalarField::typeName;
		}
		else if (isA<mixedFvPatchScalarField>(tbf[patchi]))
		{
			hbt[patchi] = mixedEnthalpyFvPatchScalarField::typeName;
		}
	}

	return hbt;
}


void tnbLib::basicThermo::hBoundaryCorrection(volScalarField& h)
{
	volScalarField::GeometricBoundaryField& hbf = h.boundaryField();

	forAll(hbf, patchi)
	{
		if (isA<gradientEnthalpyFvPatchScalarField>(hbf[patchi]))
		{
			refCast<gradientEnthalpyFvPatchScalarField>(hbf[patchi]).gradient()
				= hbf[patchi].fvPatchField::snGrad();
		}
		else if (isA<mixedEnthalpyFvPatchScalarField>(hbf[patchi]))
		{
			refCast<mixedEnthalpyFvPatchScalarField>(hbf[patchi]).refGrad()
				= hbf[patchi].fvPatchField::snGrad();
		}
	}
}


tnbLib::wordList tnbLib::basicThermo::eBoundaryTypes()
{
	const volScalarField::GeometricBoundaryField& tbf = T_.boundaryField();

	wordList ebt = tbf.types();

	forAll(tbf, patchi)
	{
		if (isA<fixedValueFvPatchScalarField>(tbf[patchi]))
		{
			ebt[patchi] = fixedInternalEnergyFvPatchScalarField::typeName;
		}
		else if
			(
				isA<zeroGradientFvPatchScalarField>(tbf[patchi])
				|| isA<fixedGradientFvPatchScalarField>(tbf[patchi])
				)
		{
			ebt[patchi] = gradientInternalEnergyFvPatchScalarField::typeName;
		}
		else if (isA<mixedFvPatchScalarField>(tbf[patchi]))
		{
			ebt[patchi] = mixedInternalEnergyFvPatchScalarField::typeName;
		}
	}

	return ebt;
}


void tnbLib::basicThermo::eBoundaryCorrection(volScalarField& e)
{
	volScalarField::GeometricBoundaryField& ebf = e.boundaryField();

	forAll(ebf, patchi)
	{
		if (isA<gradientInternalEnergyFvPatchScalarField>(ebf[patchi]))
		{
			refCast<gradientInternalEnergyFvPatchScalarField>(ebf[patchi])
				.gradient() = ebf[patchi].fvPatchField::snGrad();
		}
		else if (isA<mixedInternalEnergyFvPatchScalarField>(ebf[patchi]))
		{
			refCast<mixedInternalEnergyFvPatchScalarField>(ebf[patchi])
				.refGrad() = ebf[patchi].fvPatchField::snGrad();
		}
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicThermo::basicThermo(const fvMesh& mesh, const objectRegistry& obj)
	:
	IOdictionary
	(
		IOobject
		(
			"thermophysicalProperties",
			mesh.time().constant(),
			obj,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),

	p_
	(
		IOobject
		(
			"p",
			mesh.time().timeName(),
			obj,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	),

	psi_
	(
		IOobject
		(
			"psi",
			mesh.time().timeName(),
			obj,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(0, -2, 2, 0, 0, 0, 0)
	),

	T_
	(
		IOobject
		(
			"T",
			mesh.time().timeName(),
			obj,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	),

	mu_
	(
		IOobject
		(
			"mu",
			mesh.time().timeName(),
			obj,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(1, -1, -1, 0, 0)
	),

	alpha_
	(
		IOobject
		(
			"alpha",
			mesh.time().timeName(),
			obj,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(1, -1, -1, 0, 0)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::basicThermo::~basicThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::volScalarField& tnbLib::basicThermo::p()
{
	return p_;
}


const tnbLib::volScalarField& tnbLib::basicThermo::p() const
{
	return p_;
}


const tnbLib::volScalarField& tnbLib::basicThermo::psi() const
{
	return psi_;
}


tnbLib::volScalarField& tnbLib::basicThermo::h()
{
	notImplemented("basicThermo::h()");
	return const_cast<volScalarField&>(volScalarField::null());
}


const tnbLib::volScalarField& tnbLib::basicThermo::h() const
{
	notImplemented("basicThermo::h() const");
	return volScalarField::null();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::h
(
	const scalarField& T,
	const labelList& cells
) const
{
	notImplemented
	(
		"basicThermo::h"
		"(const scalarField& T, const labelList& cells) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::h
(
	const scalarField& T,
	const label patchi
) const
{
	notImplemented
	(
		"basicThermo::h"
		"(const scalarField& T, const label patchi) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::volScalarField& tnbLib::basicThermo::hs()
{
	notImplemented("basicThermo::hs()");
	return const_cast<volScalarField&>(volScalarField::null());
}


const tnbLib::volScalarField& tnbLib::basicThermo::hs() const
{
	notImplemented("basicThermo::hs() const");
	return volScalarField::null();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::hs
(
	const scalarField& T,
	const labelList& cells
) const
{
	notImplemented
	(
		"basicThermo::hs"
		"(const scalarField& T, const labelList& cells) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::hs
(
	const scalarField& T,
	const label patchi
) const
{
	notImplemented
	(
		"basicThermo::hs"
		"(const scalarField& T, const label patchi) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::basicThermo::hc() const
{
	notImplemented("basicThermo::hc()");
	return volScalarField::null();
}


tnbLib::volScalarField& tnbLib::basicThermo::e()
{
	notImplemented("basicThermo::e()");
	return const_cast<volScalarField&>(volScalarField::null());
}


const tnbLib::volScalarField& tnbLib::basicThermo::e() const
{
	notImplemented("basicThermo::e()");
	return volScalarField::null();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::e
(
	const scalarField& T,
	const labelList& cells
) const
{
	notImplemented
	(
		"basicThermo::e"
		"(const scalarField& T, const labelList& cells) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::e
(
	const scalarField& T,
	const label patchi
) const
{
	notImplemented
	(
		"basicThermo::e"
		"(const scalarField& T, const label patchi) const"
	);
	return tmp<scalarField>(NULL);
}


const tnbLib::volScalarField& tnbLib::basicThermo::T() const
{
	return T_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::Cp
(
	const scalarField& T,
	const label patchi
) const
{
	notImplemented
	(
		"basicThermo::Cp"
		"(const scalarField& T, const label patchi) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::Cp
(
	const scalarField& T,
	const labelList& cells
) const
{
	notImplemented
	(
		"basicThermo::Cp"
		"(const scalarField& T, const labelList& cells) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::basicThermo::Cp() const
{
	notImplemented("basicThermo::Cp() const");
	return volScalarField::null();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::basicThermo::Cv
(
	const scalarField& T,
	const label patchi
) const
{
	notImplemented
	(
		"basicThermo::Cv"
		"(const scalarField& T, const label patchi) const"
	);
	return tmp<scalarField>(NULL);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::basicThermo::Cv() const
{
	notImplemented("basicThermo::Cv() const");
	return volScalarField::null();
}


const tnbLib::volScalarField& tnbLib::basicThermo::mu() const
{
	return mu_;
}


const tnbLib::volScalarField& tnbLib::basicThermo::alpha() const
{
	return alpha_;
}


bool tnbLib::basicThermo::read()
{
	return regIOobject::read();
}


// ************************************************************************* //