#include <FadOneField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<int nVars>
tnbLib::tmp<tnbLib::Field<tnbLib::FadOne<nVars> > >
tnbLib::ValueFadOneField(const UList<scalar>& u)
{
	tmp<tnbLib::Field<FadOne<nVars> > > tr
	(
		new tnbLib::Field<FadOne<nVars> >(u.size())
	);

	Field<FadOne<nVars> >& r = tr();

	forAll(r, i)
	{
		r[i].value() = u[i];
	}

	return tr;
}


template<int nVars>
tnbLib::tmp<tnbLib::scalarField> tnbLib::FadOneValue(const Field<FadOne<nVars> >& u)
{
	tmp<scalarField> tr(new scalarField(u.size()));
	scalarField& r = tr();

	forAll(r, i)
	{
		r[i] = u[i].value();
	}

	return tr;
}


template<int nVars>
void tnbLib::FadOneSetValue
(
	Field<FadOne<nVars> >& u,
	const scalarField& val
)
{
	forAll(u, i)
	{
		u[i].value() = val[i];
	}
}


template<int nVars>
tnbLib::tmp<tnbLib::scalarField> tnbLib::FadOneDeriv
(
	const Field<FadOne<nVars> >& u,
	const direction d
)
{
	tmp<scalarField> tr(new scalarField(u.size()));
	scalarField& r = tr();

	forAll(r, i)
	{
		r[i] = u[i].deriv(d);
	}

	return tr;
}


template<int nVars>
void tnbLib::FadOneSetDeriv
(
	Field<FadOne<nVars> >& u,
	const direction d,
	const scalarField& der
)
{
	forAll(u, i)
	{
		u[i].deriv(d) = der[i];
	}
}


// ************************************************************************* //