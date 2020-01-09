#include <GeometricScalarField.hxx>

#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
#include <GeometricFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void stabilise
	(
		GeometricField<scalar, PatchField, GeoMesh>& result,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		stabilise(result.internalField(), gsf.internalField(), ds.value());
		stabilise(result.boundaryField(), gsf.boundaryField(), ds.value());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > stabilise
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh> > tRes
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"stabilise(" + gsf.name() + ',' + ds.name() + ')',
					gsf.instance(),
					gsf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gsf.mesh(),
				ds.dimensions() + gsf.dimensions()
				)
		);

		stabilise(tRes(), gsf, ds);

		return tRes;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > stabilise
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf,
		const dimensioned<scalar>& ds
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tRes
		(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf,
				"stabilise(" + gsf.name() + ',' + ds.name() + ')',
				ds.dimensions() + gsf.dimensions()
			)
		);

		stabilise(tRes(), gsf, ds);

		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf);

		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void add(GeometricField<scalar, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	         const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const scalar& t1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) + gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
			                                                                 dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const scalar& t1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2) { return dimensioned<scalar>(t1) + tgf2; }
	
	template<template<class> class PatchField, class GeoMesh>
	void add(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	         const dimensioned<scalar>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const scalar& t2) { return gf1 + dimensioned<scalar>(t2); }

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<scalar>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
			                                                                 gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const scalar& t2)
	{
		return tgf1 + dimensioned<scalar>(t2);
	}
		
	template<template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<scalar, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const scalar& t1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) - gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
			                                                                 dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const scalar& t1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2) { return dimensioned<scalar>(t1) - tgf2; }
	
	template<template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const dimensioned<scalar>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const scalar& t2) { return gf1 - dimensioned<scalar>(t2); }

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<scalar>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
			                                                                 gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const scalar& t2)
	{
		return tgf1 - dimensioned<scalar>(t2);
	}

		
	template<template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                 gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                 gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
		
	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                 gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                 gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

		
	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<scalar, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
			                                                                 dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tgf2) { return dimensioned<scalar>(t1) / tgf2; }

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<template<class> class PatchField, class GeoMesh>
	void pow
	(
		GeometricField<scalar, PatchField, GeoMesh>& Pow,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		pow(Pow.internalField(), gsf1.internalField(), gsf2.internalField());
		pow(Pow.boundaryField(), gsf1.boundaryField(), gsf2.boundaryField());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
					gsf1.instance(),
					gsf1.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gsf1.mesh(),
				pow
				(
					gsf1.dimensions(),
					dimensionedScalar("1", gsf2.dimensions(), 1.0)
				)
				)
		);

		pow(tPow(), gsf1, gsf2);

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1 = tgsf1();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf1,
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				pow
				(
					gsf1.dimensions(),
					dimensionedScalar("1", gsf2.dimensions(), 1.0)
				)
			)
		);

		pow(tPow(), gsf1, gsf2);

		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf1);

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2 = tgsf2();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf2,
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				pow
				(
					gsf1.dimensions(),
					dimensionedScalar("1", gsf2.dimensions(), 1.0)
				)
			)
		);

		pow(tPow(), gsf1, gsf2);

		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf2);

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1 = tgsf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2 = tgsf2();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			reuseTmpTmpGeometricField
			<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf1,
				tgsf2,
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				pow
				(
					gsf1.dimensions(),
					dimensionedScalar("1", gsf2.dimensions(), 1.0)
				)
			)
		);

		pow(tPow(), gsf1, gsf2);

		reuseTmpTmpGeometricField
			<scalar, scalar, scalar, scalar, PatchField, GeoMesh>
			::clear(tgsf1, tgsf2);

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	void pow
	(
		GeometricField<scalar, PatchField, GeoMesh>& tPow,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		pow(tPow.internalField(), gsf.internalField(), ds.value());
		pow(tPow.boundaryField(), gsf.boundaryField(), ds.value());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensionedScalar& ds
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"pow(" + gsf.name() + ',' + ds.name() + ')',
					gsf.instance(),
					gsf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gsf.mesh(),
				pow(gsf.dimensions(), ds)
				)
		);

		pow(tPow(), gsf, ds);

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf,
		const dimensionedScalar& ds
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf,
				"pow(" + gsf.name() + ',' + ds.name() + ')',
				pow(gsf.dimensions(), ds)
			)
		);

		pow(tPow(), gsf, ds);

		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf);

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const scalar& s
	)
	{
		return pow(gsf, dimensionedScalar(s));
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf,
		const scalar& s
	)
	{
		return pow(tgsf, dimensionedScalar(s));
	}


	template<template<class> class PatchField, class GeoMesh>
	void pow
	(
		GeometricField<scalar, PatchField, GeoMesh>& tPow,
		const dimensioned<scalar>& ds,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		pow(tPow.internalField(), ds.value(), gsf.internalField());
		pow(tPow.boundaryField(), ds.value(), gsf.boundaryField());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const dimensionedScalar& ds,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"pow(" + ds.name() + ',' + gsf.name() + ')',
					gsf.instance(),
					gsf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gsf.mesh(),
				pow(ds, gsf.dimensions())
				)
		);

		pow(tPow(), ds, gsf);

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const dimensionedScalar& ds,
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tPow
		(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf,
				"pow(" + ds.name() + ',' + gsf.name() + ')',
				pow(ds, gsf.dimensions())
			)
		);

		pow(tPow(), ds, gsf);

		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf);

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const scalar& s,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		return pow(dimensionedScalar(s), gsf);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > pow
	(
		const scalar& s,
		const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf
	)
	{
		return pow(dimensionedScalar(s), tgsf);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class PatchField, class GeoMesh>
	void pow3(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow3(res.internalField(), gf1.internalField());
		tnbLib::pow3(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow3(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("pow3" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pow3(gf1.dimensions())));
		tnbLib::pow3(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow3(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow3" "(" + gf1.name() + ')',
			                                                                 pow3(gf1.dimensions())));
		tnbLib::pow3(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void pow4(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow4(res.internalField(), gf1.internalField());
		tnbLib::pow4(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow4(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("pow4" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pow4(gf1.dimensions())));
		tnbLib::pow4(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow4(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow4" "(" + gf1.name() + ')',
			                                                                 pow4(gf1.dimensions())));
		tnbLib::pow4(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void pow5(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow5(res.internalField(), gf1.internalField());
		tnbLib::pow5(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow5(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("pow5" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pow5(gf1.dimensions())));
		tnbLib::pow5(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow5(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow5" "(" + gf1.name() + ')',
			                                                                 pow5(gf1.dimensions())));
		tnbLib::pow5(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void pow6(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow6(res.internalField(), gf1.internalField());
		tnbLib::pow6(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow6(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("pow6" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pow6(gf1.dimensions())));
		tnbLib::pow6(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow6(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow6" "(" + gf1.name() + ')',
			                                                                 pow6(gf1.dimensions())));
		tnbLib::pow6(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void sqrt(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sqrt(res.internalField(), gf1.internalField());
		tnbLib::sqrt(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sqrt(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("sqrt" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			sqrt(gf1.dimensions())));
		tnbLib::sqrt(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sqrt(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sqrt" "(" + gf1.name() + ')',
			                                                                 sqrt(gf1.dimensions())));
		tnbLib::sqrt(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void sign(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sign(res.internalField(), gf1.internalField());
		tnbLib::sign(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sign(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("sign" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			sign(gf1.dimensions())));
		tnbLib::sign(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sign(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sign" "(" + gf1.name() + ')',
			                                                                 sign(gf1.dimensions())));
		tnbLib::sign(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void pos(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pos(res.internalField(), gf1.internalField());
		tnbLib::pos(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("pos" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pos(gf1.dimensions())));
		tnbLib::pos(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pos" "(" + gf1.name() + ')',
			                                                                 pos(gf1.dimensions())));
		tnbLib::pos(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void neg(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::neg(res.internalField(), gf1.internalField());
		tnbLib::neg(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("neg" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			neg(gf1.dimensions())));
		tnbLib::neg(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "neg" "(" + gf1.name() + ')',
			                                                                 neg(gf1.dimensions())));
		tnbLib::neg(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

		
	template <template<class> class PatchField, class GeoMesh>
	void exp(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::exp(res.internalField(), gf1.internalField());
		tnbLib::exp(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> exp(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("exp" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::exp(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> exp(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "exp" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::exp(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void log(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::log(res.internalField(), gf1.internalField());
		tnbLib::log(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("log" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::log(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "log" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::log(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void log10(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::log10(res.internalField(), gf1.internalField());
		tnbLib::log10(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log10(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("log10" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::log10(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log10(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "log10" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::log10(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void sin(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sin(res.internalField(), gf1.internalField());
		tnbLib::sin(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sin(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("sin" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::sin(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sin(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sin" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::sin(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void cos(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cos(res.internalField(), gf1.internalField());
		tnbLib::cos(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cos(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cos" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::cos(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "cos" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::cos(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void tan(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tan(res.internalField(), gf1.internalField());
		tnbLib::tan(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tan(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("tan" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::tan(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tan(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "tan" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::tan(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void asin(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::asin(res.internalField(), gf1.internalField());
		tnbLib::asin(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asin(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("asin" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::asin(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asin(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "asin" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::asin(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void acos(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::acos(res.internalField(), gf1.internalField());
		tnbLib::acos(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acos(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("acos" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::acos(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "acos" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::acos(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void atan(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::atan(res.internalField(), gf1.internalField());
		tnbLib::atan(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("atan" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::atan(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "atan" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::atan(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void sinh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sinh(res.internalField(), gf1.internalField());
		tnbLib::sinh(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sinh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("sinh" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::sinh(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sinh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sinh" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::sinh(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void cosh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cosh(res.internalField(), gf1.internalField());
		tnbLib::cosh(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cosh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cosh" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::cosh(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cosh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "cosh" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::cosh(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void tanh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tanh(res.internalField(), gf1.internalField());
		tnbLib::tanh(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tanh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("tanh" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::tanh(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tanh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "tanh" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::tanh(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void asinh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::asinh(res.internalField(), gf1.internalField());
		tnbLib::asinh(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asinh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("asinh" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::asinh(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asinh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "asinh" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::asinh(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void acosh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::acosh(res.internalField(), gf1.internalField());
		tnbLib::acosh(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acosh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("acosh" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::acosh(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acosh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "acosh" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::acosh(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void atanh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::atanh(res.internalField(), gf1.internalField());
		tnbLib::atanh(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atanh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("atanh" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::atanh(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atanh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "atanh" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::atanh(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void erf(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::erf(res.internalField(), gf1.internalField());
		tnbLib::erf(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erf(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("erf" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::erf(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erf(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "erf" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::erf(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void erfc(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::erfc(res.internalField(), gf1.internalField());
		tnbLib::erfc(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erfc(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("erfc" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::erfc(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erfc(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "erfc" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::erfc(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void lgamma(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::lgamma(res.internalField(), gf1.internalField());
		tnbLib::lgamma(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> lgamma(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("lgamma" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::lgamma(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> lgamma(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "lgamma" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::lgamma(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void j0(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::j0(res.internalField(), gf1.internalField());
		tnbLib::j0(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j0(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("j0" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::j0(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "j0" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::j0(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void j1(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::j1(res.internalField(), gf1.internalField());
		tnbLib::j1(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j1(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("j1" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::j1(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j1(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "j1" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::j1(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void y0(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::y0(res.internalField(), gf1.internalField());
		tnbLib::y0(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y0(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("y0" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::y0(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "y0" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::y0(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void y1(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::y1(res.internalField(), gf1.internalField());
		tnbLib::y1(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y1(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("y1" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			trans(gf1.dimensions())));
		tnbLib::y1(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y1(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "y1" "(" + gf1.name() + ')',
			                                                                 trans(gf1.dimensions())));
		tnbLib::y1(tRes(), gf1);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BesselFunc(func)                                                     \
                                                                            \
template<template<class> class PatchField, class GeoMesh>                   \
void func                                                                   \
(                                                                           \
    GeometricField<scalar, PatchField, GeoMesh>& gsf,                       \
    const int n,                                                            \
    const GeometricField<scalar, PatchField, GeoMesh>& gsf1                 \
)                                                                           \
{                                                                           \
    func(gsf.internalField(), n, gsf1.internalField());                     \
    func(gsf.boundaryField(), n, gsf1.boundaryField());                     \
}                                                                           \
                                                                            \
template<template<class> class PatchField, class GeoMesh>                   \
tmp<GeometricField<scalar, PatchField, GeoMesh> > func                      \
(                                                                           \
    const int n,                                                            \
    const GeometricField<scalar, PatchField, GeoMesh>& gsf                  \
)                                                                           \
{                                                                           \
    if (!gsf.dimensions().dimensionless())                                  \
    {                                                                       \
        FatalErrorIn                                                        \
        (                                                                   \
            #func"(const int n, "                                           \
            "const GeometricField<scalar, PatchField, GeoMesh>& gsf)"       \
        )   << "gsf not dimensionless"                                      \
            << abort(FatalError);                                           \
    }                                                                       \
                                                                            \
    tmp<GeometricField<scalar, PatchField, GeoMesh> > tFunc                 \
    (                                                                       \
        new GeometricField<scalar, PatchField, GeoMesh>                     \
        (                                                                   \
            IOobject                                                        \
            (                                                               \
                #func "(" + gsf.name() + ')',                               \
                gsf.instance(),                                             \
                gsf.db(),                                                   \
                IOobject::NO_READ,                                          \
                IOobject::NO_WRITE                                          \
            ),                                                              \
            gsf.mesh(),                                                     \
            dimless                                                         \
        )                                                                   \
    );                                                                      \
                                                                            \
    func(tFunc(), n, gsf);                                                  \
                                                                            \
    return tFunc;                                                           \
}                                                                           \
                                                                            \
template<template<class> class PatchField, class GeoMesh>                   \
tmp<GeometricField<scalar, PatchField, GeoMesh> > func                      \
(                                                                           \
    const int n,                                                            \
    const tmp<GeometricField<scalar, PatchField, GeoMesh> >& tgsf           \
)                                                                           \
{                                                                           \
    const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();        \
                                                                            \
    if (!gsf.dimensions().dimensionless())                                  \
    {                                                                       \
        FatalErrorIn                                                        \
        (                                                                   \
            #func"(const int n, "                                           \
            "const tmp<GeometricField<scalar, PatchField, GeoMesh> >& gsf)" \
        )   << " : gsf not dimensionless"                                   \
            << abort(FatalError);                                           \
    }                                                                       \
                                                                            \
    tmp<GeometricField<scalar, PatchField, GeoMesh> > tFunc                 \
    (                                                                       \
        reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New    \
        (                                                                   \
            tgsf,                                                           \
            #func "(" + gsf.name() + ')',                                   \
            dimless                                                         \
        )                                                                   \
    );                                                                      \
                                                                            \
    func(tFunc(), n, gsf);                                                  \
                                                                            \
    reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>             \
    ::clear(tgsf);                                                          \
                                                                            \
    return tFunc;                                                           \
}

		
	template <template<class> class PatchField, class GeoMesh>
	void jn(GeometricField<scalar, PatchField, GeoMesh>& gsf, const int n,
	        const GeometricField<scalar, PatchField, GeoMesh>& gsf1)
	{
		jn(gsf.internalField(), n, gsf1.internalField());
		jn(gsf.boundaryField(), n, gsf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> jn(const int n,
	                                                    const GeometricField<scalar, PatchField, GeoMesh>& gsf)
	{
		if (!gsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "jn""(const int n, " "const GeometricField<scalar, PatchField, GeoMesh>& gsf)" ) <<
				"gsf not dimensionless" << abort(FatalError);
		}
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("jn" "(" + gsf.name() + ')', gsf.instance(), gsf.db(), IOobject::NO_READ, IOobject::NO_WRITE), gsf.mesh(),
			dimless));
		jn(tFunc(), n, gsf);
		return tFunc;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> jn(const int n,
	                                                    const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();
		if (!gsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "jn""(const int n, " "const tmp<GeometricField<scalar, PatchField, GeoMesh> >& gsf)" ) <<
				" : gsf not dimensionless" << abort(FatalError);
		}
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgsf, "jn" "(" + gsf.name() + ')', dimless));
		jn(tFunc(), n, gsf);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf);
		return tFunc;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void yn(GeometricField<scalar, PatchField, GeoMesh>& gsf, const int n,
	        const GeometricField<scalar, PatchField, GeoMesh>& gsf1)
	{
		yn(gsf.internalField(), n, gsf1.internalField());
		yn(gsf.boundaryField(), n, gsf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> yn(const int n,
	                                                    const GeometricField<scalar, PatchField, GeoMesh>& gsf)
	{
		if (!gsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "yn""(const int n, " "const GeometricField<scalar, PatchField, GeoMesh>& gsf)" ) <<
				"gsf not dimensionless" << abort(FatalError);
		}
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("yn" "(" + gsf.name() + ')', gsf.instance(), gsf.db(), IOobject::NO_READ, IOobject::NO_WRITE), gsf.mesh(),
			dimless));
		yn(tFunc(), n, gsf);
		return tFunc;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> yn(const int n,
	                                                    const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();
		if (!gsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "yn""(const int n, " "const tmp<GeometricField<scalar, PatchField, GeoMesh> >& gsf)" ) <<
				" : gsf not dimensionless" << abort(FatalError);
		}
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgsf, "yn" "(" + gsf.name() + ')', dimless));
		yn(tFunc(), n, gsf);
		reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::clear(tgsf);
		return tFunc;
	}

#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //
